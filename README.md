## yoDownet

yoDownet is an open-source && free graphical download manager project that tries to be simple and minimal, also for sake of humor it's described as "The Previous Generation Graphical Download Manager".

### Basic features

* Increases download speeds (It just does!).
* Concurrent file downoading.
* Safe Pause/Resume On Files
* Multilingual


### Languages

yoDownet has been translated into below languages:
* English
* Estonian
* Persian
* Turkish
* Vietnamese
* Dutch
* Czech

#### Translations status

![yoDownet translation status on transifex](https://www.transifex.com/projects/p/yodownet/resource/ts/chart/image_png "yoDownet translation status on transifex")

We're handling translations via transifex which rocks **<3**

[transifex.com/projects/p/yodownet][Transifex]


### Gnu/Linux installer packages
Here you can get a list of packages available for specific Linux distro.

#### Arch Linux
* [yodownet][ArchlinuxAUR] _AUR pkg_ - __[Alir3z4][Alir3z4Account]__
* [yodownet-git][ArchlinuxAURgit] _AUR git pkg_ - __[Alir3z4][Alir3z4Account]__


#### Frugalware
* [yodownet][frugalwarLinuxi686] _Arch: i686_ - __Slown__ \<slown at frugalware.org\>
* [yodownet][frugalwarLinuxX86_64] _Arch: x86-64_ - __Slown__ \<slown at frugalware.org\>

#### Haikuware
* [yoDownet][yoDownetHaikuwarePkg]: [_Giovanni Mugnai (Giova84)_](http://haikuware.com/giova84/)



### Build
yoDownet is built on top of the Qt/C++ toolkit, compile and build the project is simple like any other project out there, no godzilla will jump out on you ;)

#### Build yoDownet on Gnu/Linux

To compile|build yoDownet on gnu/linux the main dependency is [Qt][Qt], Just Qt and nothing else!
To build yoDownet, execute at the extracted source directory

##### Compile/Build

```
$ qmake -config release
$ make
```

##### Install

```
$ make install
```
That's it, now if you are a [KDE][kde]|* [DE][de] user you can find yoDownet in Network|Internet category or just type it out at [Konsole][konsole]|Command-Line ;)

```
$ yoDownet
```

##### Clean build

```
$ make clean
```

##### Debug mode

Add __-config debug__ to the qmake invocation
```
$ qmake -config debug
```

##### Run Tests

```
$ qmake "CONFIG += qtestlib console"
```


### License
yoDownet is released under GPLv3. Free and OpenSource ;)


### Resuorces
* [SourceForge homepage][SourceForgeHomePage]
* [Blog][Blog]
* [Github repo][GithubRepo]
* [Issue tracker][IssueTracker]
* [Documentation][wiki]
* [Translations][Transifex]
* [Mailing list][MailMan]
* [Source code archive][SourceArchive]



[Qt]: http://qt-project.org/
[qmake]: http://en.wikipedia.org/wiki/Qmake
[kde]: http://www.kde.org/
[de]: http://en.wikipedia.org/wiki/Desktop_environment
[konsole]: http://konsole.kde.org/
[Alir3z4Account]: https://github.com/Alir3z4
[ArchlinuxAUR]: http://aur.archlinux.org/packages.php?ID=56565
[ArchlinuxAURgit]: https://aur.archlinux.org/packages/yodownet-git/
[frugalwarLinuxi686]: http://frugalware.org/packages/152626
[frugalwarLinuxX86_64]: http://frugalware.org/packages/152625
[yoDownetHaikuwarePkg]: http://haikuware.com/directory/view-details/internet-network/utilities/yodownet-download-manager
[SourceForgeHomePage]: http://sf.net/p/yodownet/
[Blog]: https://sourceforge.net/p/yodownet/blog/
[GithubRepo]: https://github.com/Alir3z4/yoDownet
[IssueTracker]: https://github.com/Alir3z4/yoDownet/issues
[wiki]: https://github.com/Alir3z4/yoDownet/wiki
[Transifex]: https://www.transifex.com/projects/p/yodownet/
[MailMan]: https://sourceforge.net/p/yodownet/mailman/
[SourceArchive]: https://sourceforge.net/projects/yodownet/files/sources/
