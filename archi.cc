/* Tower Toppler - Nebulus
 * Copyright (C) 2000-2004  Andreas Röver
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "archi.h"
#include "decl.h"

#if (SYSTEM == SYS_WINDOWS)
//#define _WINDOWS
//#define ZLIB_DLL
#endif

#include <zlib.h>
#include <string.h>
#include <stdlib.h>

/* this value is used as a sanity check for filnename lengths
 */
#define FNAMELEN 250

archive::archive(FILE *stream) : f(stream) {

  assert(f, "Data file not found");

  /* find out the number of files inside the archive
   * alloce the neccessary memory
   */
  fread(&filecount, 1, 1, f);
  files = new fileindex[filecount];
  assert(files, "Failed to alloc memory for archive index.");

  /* read the information for each file */
  for (Uint8 file = 0; file < filecount; file++) {

    Uint8 strlen = 0;

    /* find ut the length of the name string */
    {
      char c;
      long currentpos = ftell(f);

      do {
        strlen++;
        assert(strlen <= FNAMELEN, "Filename too long, datafile corrupt?");
        fread(&c, 1, 1, f);
      } while (c);

      fseek(f, currentpos, SEEK_SET);
    }

    /* alloc memory for string and read it */
    files[file].name = new char[strlen];
    for (int pos = 0; pos < strlen; pos++)
      fread(&files[file].name[pos], 1, 1, f);

    Uint8 tmp;

    /* load start from archive */
    fread(&tmp, 1, 1, f);
    files[file].start = ((Uint32)(tmp)) << 0;
    fread(&tmp, 1, 1, f);
    files[file].start |= ((Uint32)(tmp)) << 8;
    fread(&tmp, 1, 1, f);
    files[file].start |= ((Uint32)(tmp)) << 16;
    fread(&tmp, 1, 1, f);
    files[file].start |= ((Uint32)(tmp)) << 24;

    /* load filesize from archive */
    fread(&tmp, 1, 1, f);
    files[file].size = ((Uint32)(tmp)) << 0;
    fread(&tmp, 1, 1, f);
    files[file].size |= ((Uint32)(tmp)) << 8;
    fread(&tmp, 1, 1, f);
    files[file].size |= ((Uint32)(tmp)) << 16;
    fread(&tmp, 1, 1, f);
    files[file].size |= ((Uint32)(tmp)) << 24;

    /* load compressed size from archive */
    fread(&tmp, 1, 1, f);
    files[file].compress = ((Uint32)(tmp)) << 0;
    fread(&tmp, 1, 1, f);
    files[file].compress |= ((Uint32)(tmp)) << 8;
    fread(&tmp, 1, 1, f);
    files[file].compress |= ((Uint32)(tmp)) << 16;
    fread(&tmp, 1, 1, f);
    files[file].compress |= ((Uint32)(tmp)) << 24;
  }
}

archive::~archive() {

  /* free memory allocated for filenames */
  for (int i = 0; i < filecount; i++)
    delete [] files[i].name;

  /* free the file header array */
  delete [] files;

  fclose(f);
}

file::file(const archive *arc, const char *name) : bufferpos(0) {

  for (Uint8 i = 0; i < arc->filecount; i++) {
    if (strncmp(name, arc->files[i].name, FNAMELEN) == 0) {

      /* allocate buffer for compressed data */
      Uint8 *b = new Uint8[arc->files[i].compress];

      /* allocate buffer for uncompressed data */
      fsize = arc->files[i].size;
      buffer = new Uint8[fsize];

      /* read the compressed data */
      fseek(arc->f, arc->files[i].start, SEEK_SET);
      fread(b, arc->files[i].compress, 1, arc->f);

      /* decompress it and check results */
      assert(uncompress(buffer, &fsize, b, arc->files[i].compress) == Z_OK, "Decompression problem, data file corrupt?");
      assert(fsize == arc->files[i].size, "Data file corrupt.");

      /* free temporary buffer */
      delete [] b;

      return;
    }
  }

  /* if we arrive here we couldn't find the file we looked for */
  assert(0, "File not found in archive!");
}

file::~file() { delete [] buffer; }

Uint32 file::read(void *buf, Uint32 size) {
  memcpy(buf, &buffer[bufferpos], size);
  bufferpos += size;
  return size;
}

Uint8 file::getbyte(void) {
  return buffer[bufferpos++];
}

Uint16 file::getword(void) {
  Uint16 w = (Uint16)buffer[bufferpos] + ((Uint16)buffer[bufferpos+1] << 8);
  bufferpos+=2;
  return w;
}

SDL_RWops *file::rwOps(void) {
  return SDL_RWFromMem(buffer, fsize);
}


archive * dataarchive;
