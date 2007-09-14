Name: toppler
Version: 1.1.1
Release: 1


URL: http://toppler.soureforge.net

License: GPL
Group: Amusements/Games

BuildRoot: %{_tmppath}/%{name}-root

Requires: SDL >= 1.2.2, SDL_mixer >= 1.2.2, zlib, libstdc++
BuildRequires: SDL-devel >= 1.2.2
AutoReqProv: no

Source0: %{name}-%{version}.tar.gz
#Patch0: %{name}-%{version}-patch0.diff.gz
#Patch1: %{name}-%{version}-patch1.diff.gz

Summary: Tower Toppler

%description 
Reimplementation of the old game (aka Nebulous). In the game you have
to climb a tower with lots of strange inhabitants that try to push you
down. Your only defence is a snowball you can throw and your skill to
avoid these beings.

%prep

%setup -q
#%patch0 -p1
#%patch1 -p1


%build

%configure
%{__make}


%install
rm -rf $RPM_BUILD_ROOT
%makeinstall


%clean
rm -rf $RPM_BUILD_ROOT


%files
%defattr(-,root,root)

%doc README COPYING AUTHORS NEWS ChangeLog

%{_bindir}/*
%{_datadir}/*


%changelog
* Sun Oct  6 2002 Chong Kai Xiong <descender@phreaker.net>
- Initial build.

%post
chgrp games /usr/bin/toppler;
chmod g+s /usr/bin/toppler
install -d /usr/var/toppler
touch /usr/var/toppler/toppler.hsc
chgrp games /usr/var/toppler
chmod g+rw /usr/var/toppler
chgrp games /usr/var/toppler/toppler.hsc
chmod g+rw /usr/var/toppler/toppler.hsc

