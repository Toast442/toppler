#!/bin/sh

SDL=$HOME/projects/root/Library/Frameworks/SDL_2.0
BUNDLE=Toppler.app

rm -rf ${BUNDLE}

mkdir -p ${BUNDLE}/Contents/MacOS
mkdir -p ${BUNDLE}/Contents/Resources
mkdir -p ${BUNDLE}/Contents/Frameworks

cat macfiles/Info.plist | sed -e "s/@VERSION@/${1}/" > ${BUNDLE}/Contents/Info.plist
cp macfiles/PkgInfo ${BUNDLE}/Contents
cp macfiles/Toppler.icns ${BUNDLE}/Contents/Resources
cp -a $SDL/SDL2.framework ${BUNDLE}/Contents/Frameworks
cp -a $SDL/SDL2_image.framework ${BUNDLE}/Contents/Frameworks
cp -a $SDL/SDL2_mixer.framework ${BUNDLE}/Contents/Frameworks
cp -a toppler ${BUNDLE}/Contents/MacOS
cp -a *.ttm ${BUNDLE}/Contents/Resources
cp -a *.ogg ${BUNDLE}/Contents/Resources
cp -a toppler.dat ${BUNDLE}/Contents/Resources


rm -vf ${BUNDLE}/Contents/Frameworks/SDL2.framework/Versions/Current/Headers/SDL2

MACOS_APP_BIN=${BUNDLE}/Contents/MacOS/Toppler

for old in `otool -L $MACOS_APP_BIN | grep @rpath | cut -f2 | cut -d' ' -f1`; do
    new=`echo $old | sed -e "s/@rpath/@executable_path\/..\/Frameworks/"`
    echo "Replacing '$old' with '$new'"
    install_name_tool -change $old $new $MACOS_APP_BIN
done

pushd ${BUNDLE}/Contents/Frameworks > /dev/null 2>&1
signframework *
popd > /dev/null 2>&1
sign --options=runtime --entitlements=macfiles/toppler-Entitlements.plist ${BUNDLE}

VERSION=$(/usr/libexec/PlistBuddy  -c "Print CFBundleGetInfoString" ${BUNDLE}/Contents/Info.plist)

ditto -c -k --keepParent ${BUNDLE} Toppler-$VERSION.zip