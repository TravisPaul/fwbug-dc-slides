#include <curses.h>
#include <stdlib.h>
#include <string.h>

// Dreamcast console is 30 x 80
#define ROWS 30
#define COLS 80
#define TITLE_MAX (COLS - 2) - 5

#define SLIDES 12

WINDOW *win;

typedef void (*slide_fn) (void);

typedef struct slide_t {
    char title[TITLE_MAX];
    slide_fn slide;
} slide_t;

struct slide_t slides[SLIDES];

static void
center(int row, const char * str) {
    move(row, (COLS - strlen(str)) / 2);
    addstr(str);
    refresh();
}

static void
template(int slide) {
    char buffer[6];
    clear();
    if (slide >= 0 && slide <= SLIDES - 1) {
        wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
        move(0, 2);
        addstr(slides[slide].title);
        move(0, 74);
        sprintf(buffer, "%d/%d", slide + 1, SLIDES); 
        addstr(buffer);
        slides[slide].slide();
    } else {
        sprintf(buffer, "no #%d", slide + 1); 
        center(ROWS / 2, buffer);
    }
    move(ROWS - 1, COLS - 1);
    refresh();
}

static void
toc(void) {
    int i = 0;
    char buffer[TITLE_MAX];
    clear();
    wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
    center(0, "TABLE OF CONTENTS");
    for (i = 0; i < SLIDES; i++) {
        move(i+1, 8);
        sprintf(buffer, "%d. %s", i + 1, slides[i].title);
        addstr(buffer);
    }
    refresh();
}


static void
slide1(void) {
    attron(A_BOLD);
    center(2, "Welcome to FWBUG Meetup #1!");
    attroff(A_BOLD);

    center(3, "Tuesday, March 8, 2016");
    center(5, "\"Of course this Meetup is about NetBSD\"");

    attron(COLOR_PAIR(1) | A_DIM);
    center(8,  "           `.-//+o++o+++//:-.           ");
    center(9, "        .:+oo+/:-----:::/+oooo/:.       ");
    center(10, "     `:+oo/-.              .-/ooo+-     ");
    center(11, "   `/oo+:`   `-//++++//:-.`   `:ooo/`   ");
    center(12, "  .+oo:`  .:+oo++/:::/++oo+/.`  ./oo+.  ");
    center(13, " .ooo.  `:oo+:.` ```   `./+oo+.   :ooo. ");
    center(14, "`+oo.  `+oo:  .:++++//-`  `/ooo-   /ooo`");
    center(15, ":oo/   +oo-  /oo/:::/+oo/`  /ooo`   +oo:");
    center(16, "+oo-  `oo+  -oo+     `:oo+  `ooo:   -+o/");
    center(17, "+oo-  `ooo  `ooo-...   ooo.  :oo+    `.`");
    center(18, "-oo+   /oo:  `:++oo+.  ooo.  -ooo       ");
    center(19, " +oo-  `+oo:`  ````` .:oo+`  -ooo       ");
    center(20, " `+oo-  `:+o++/::::/++o+:`  `+oo:       ");
    center(21, "  `+oo/.  `.://+++//:-`   `-ooo:        ");
    center(22, "    :+oo/-.`           `-/+oo/.         ");
    center(23, "      ./+ooo+//::-:://+ooo/-`           ");
    center(24, "         `.-:/++ooo++//-.`              ");
    attroff(COLOR_PAIR(1) | A_DIM); 
    use_default_colors();

    attron(COLOR_PAIR(2) | A_BLINK); 
    center(27, "       S E G A   D R E A M C A S T      ");
    attroff(COLOR_PAIR(2) | A_BLINK); 
}

static void
slide2(void) {

    attron(COLOR_PAIR(2));
    center(2, " ______   __     __     ______     __  __     ______    ");
    center(3, "/\\  ___\\ /\\ \\  _ \\ \\   /\\  =  \\   /\\ \\/\\ \\   /\\  ___\\   ");
    center(4, "\\ \\  __\\ \\ \\ \\/ \".\\ \\  \\ \\  __<   \\ \\ \\_\\ \\  \\ \\ \\__ \\  ");
    center(5, " \\ \\_\\    \\ \\__/\".~\\_\\  \\ \\_____\\  \\ \\_____\\  \\ \\_____\\ ");
    center(6, "  \\/_/     \\/_/   \\/_/   \\/_____/   \\/_____/   \\/_____/ ");
    attroff(COLOR_PAIR(2));


    move(8, 6);
    attron(A_UNDERLINE);
    addstr("Why create a Fort Wayne BSD User Group?");
    attroff(A_UNDERLINE);
    move(9, 8);
    addstr("* Why not have one more local tech Meetup?");
    move(10, 8);
    addstr("* Get more people exposed to the Unixes");
    move(11, 8);
    addstr("* Local support network for new BSD users");
    move(12, 8);
    addstr("* Study groups for BSD Certifications");

    move(14, 6);
    attron(A_UNDERLINE);
    addstr("Ideas for future Meetups:");
    attroff(A_UNDERLINE);
    move(15, 8);
    addstr("* Finding and fixing exploits with AFL");
    move(16, 8);
    addstr("* Overview of ZFS or Bhyve on FreeBSD");
    move(17, 8);
    addstr("* Demonstrating OpenBSD's exploit mitigations");
    move(18, 8);
    addstr("* Homebrew NetBSD router");
    move(19, 8);
    addstr("* Updates to this presentation");

    move(21, 6);
    attron(A_UNDERLINE);
    addstr("FWBUG needs/wants:");
    attroff(A_UNDERLINE);
    move(22, 8);
    addstr("* COLO sponsor to host server resources for:");
    move(23, 10);
    addstr("- Source Mirror - CVS (Net/Open), Subversion (Free)");
    move(24, 10);
    addstr("- Binary/Media Mirrors");
    move(25, 10);
    addstr("- CI Build hosts (Jenkins)");
    move(26, 10);
    addstr("- Misc services AFL, packaging, etc");
}

static void
slide3a (void) {
    attron(COLOR_PAIR(1));
    center(2, " . _               _____----____           ");
    center(3, "   \\\\`---______-----        ____---_       ");
    center(4, "    \\\\                 __---               ");
    center(5, "     \\\\             _------____            ");
    center(6, "      \\\\                  ____---_         ");
    center(7, "       \\\\            ___--                 ");
    center(8, "        \\`--_____----                      ");
    center(9, "         \\.                                ");
    center(10, "          \\\\                               ");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    center(11, "|     |          |||||    |||||  |||||  (R)");
    center(12, "||    |      |    |   |  |     |  |   |    ");
    center(13, "| |   |  || ||||  |   |  |        |    |   ");
    center(14, "|  |  | |  | |    |||||   |||||   |    |   ");
    center(15, "|   | | |||| |    |    |       |  |    |   ");
    center(16, "|    || |    |    |    | |     |  |   |    ");
    center(17, "|     |  |||  || ||||||   |||||  |||||     ");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(1));
    center(18, "                  __                       ");
    center(19, "                  \\ \\                      ");
    center(20, "                   \\ \\                     ");
    center(21, "                    \\ \\                    ");
    center(22, "                     \\ \\                   ");
    center(23, "                      \\ \\                  ");
    center(24, "                       \\_)                 ");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2) | A_BOLD);
    center(26, "\"Of course it runs NetBSD\"");
    attroff(COLOR_PAIR(2) | A_BOLD);
    move(29, 35);
    addstr("ascii art by R. Richardson @ bit.ly/1TivyyF");
}

static void
slide3b (void) {
    move(2, 6);
    addstr("NetBSD is a member of the BSD familiy of operating");
    move(3, 6);
    addstr("systems with a focus on portability.");

    move(5, 6);
    addstr("With its first release in April 1993, NetBSD is oldest");
    move(6, 6);
    addstr("actively maintained BSD project.");

    move(8, 6);
    addstr("It has been ported to 57 different hardware architectures,");
    move(9, 6);
    addstr("all of which can be built from the same source tree.");

    move(11, 6);
    addstr("It's portable packaging framework (pkgsrc) has been adopted");
    move(12, 6);
    addstr("by Minix and SmartOS and runs on many other operating");
    move(13, 6);
    addstr("systems such as OS X and Linux.");

    attron(A_UNDERLINE);
    move(15, 6);
    addstr("Some notable features:");
    attroff(A_UNDERLINE);
    move(16, 8);
    addstr("* Kernel Lua Bindings - Script kernel space (Firewall, GPIO, etc)");
    move(17, 8);
    addstr("* XEN DOM0/DOMU - Hypervisor and Guest");
    move(18, 8);
    addstr("* verixec - kernel based file integrity subsystem");
    move(19, 8);
    addstr("* Binary emulation - Run Linux, SunOS, FreeBSD Binaries");

    attron(COLOR_PAIR(1) | A_DIM);
    move(21, 11);
    addstr("                               __,gnnnOCCCCCOObaau,_");
    move(22, 11);
    addstr(" _._                    __,gnnCCCCCCCCOPF\"''        ~");
    move(23, 11);
    addstr("(N\\XCbngg,._____.,gnnndCCCCCCCCCCCCF\"___,,,,___");
    move(24, 11);
    addstr(" \\N\\XCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCOOOOPYvv.");
    move(25, 11);
    addstr("  \\N\\XCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCPF\"''");
    move(26, 11);
    addstr("   \\N\\XCCCCCCCCCCCCCCCCCCCCCCCCCOF\"'");
    move(27, 11);
    addstr("    \\N\\XCCCCCCCCCCCCCCCCCCCCOF\"'");
    move(28, 11);
    addstr("     \\N\\XCCCCCCCCCCCCCCCPF\"'");
    attroff(COLOR_PAIR(1) | A_DIM);

    move(29, 38);
    addstr("ascii art by NetBSD.org @ bit.ly/1psmZEY"); 
}

static void
slide4(void) {

    move(4, 12);
    addstr("The Sega Dreamcast is a home video game console");
    move(5, 12);
    addstr("released in 1998 by SEGA and was discontinued in 2001.");

    move(7, 12);
    addstr("Official games continued to be released until 2007.");

    move(9, 12);
    addstr("Some recent indie titles such as Sturmwind(2013), ");
    move(10, 12);
    addstr("Ghost Blade(2015) and Pier Solar(2015) have been ");
    move(11, 12);
    addstr("released for the console.");

    move(13, 12);
    addstr("Support for the Dreamcast was added to NetBSD in 2000.");

    attron(COLOR_PAIR(3) | A_DIM);
    move(17, 50);
    addstr("              ______ ");
    move(18, 50);
    addstr("        _____/      \\\\_____");
    move(19, 50);
    addstr("       |  _     ___   _   ||");
    move(20, 50);
    addstr("       | | \\     |   | \\  ||");
    move(21, 50);
    addstr("       | |  |    |   |  | ||");
    move(22, 50);
    addstr("       | |_/     |   |_/  ||");
    move(23, 50);
    addstr("       | | \\     |   |    ||");
    move(24, 50);
    addstr("       | |  \\.  _|_. | .  ||");
    move(25, 50);
    addstr("       |                  ||");
    move(26, 50);
    addstr("       |   1998 - 2001    ||");
    move(27, 50);
    addstr("       |                  ||");
    attroff(COLOR_PAIR(3) | A_DIM);
    attron(COLOR_PAIR(4) | A_DIM);
    move(28, 2);
    addstr(",|(.,.\\))..).|/.,(//,,..,,\\||(,,|,\\\\,.((//..).|/.,(//,,..,,\\||(,,|,\\\\,.),.,.");
    attroff(COLOR_PAIR(4) | A_DIM);

    move(29, 43);
    addstr("ascii art by ejm96 @ bit.ly/1SrkOgl");

    attron(A_UNDERLINE);
    move(16, 6);
    addstr("Dreamcast console firsts:");
    attroff(A_UNDERLINE);

    move(17, 8);
    addstr("* 128bit console");
 
    move(18, 8);
    addstr("* Built-in networking");
 
    move(19, 8);
    addstr("* Web browser");
 
    move(20, 8);
    addstr("* Motion controllers");
 
    move(21, 8);
    addstr("* Voice chat");
 
    move(22, 8);
    addstr("* Massive Multiplayer Online (MMO)");

    move(23, 8);
    addstr("* Full SD resolution (480p)");

    move(23, 8);
    addstr("* Interactive removable storage");
}

static void
slide5(void) {
    attron(A_UNDERLINE);
    move(4, 12);
    addstr("Mainboard:");
    attroff(A_UNDERLINE);
    move(5, 12);
    addstr("* 200 MHz Hitachi SuperH SH-4 32-bit RISC CPU");
    move(6, 12);
    addstr("* 16MB Main memory, 8MB Texture, 2MB Sound");
    move(7, 12);
    addstr("* 100 MHz NEC PowerVR2 GPU");
    move(8, 12);
    addstr("* Yamaha AICA sound system (64 channel PCM sound)");
    move(9, 12);
    addstr("* VGA/Component/S-Video output");
    move(10, 12);
    addstr("* 10/100 Broadband adapter");
    move(11, 12);
    addstr("* Battery backed clock");
    move(12, 12);
    addstr("* 12X GD-ROM/CD-ROM");
    move(13, 12);
    addstr("* Builtin serial port");


    attron(A_UNDERLINE);
    move(16, 12);
    addstr("Peripherals:");
    attroff(A_UNDERLINE);
    move(17, 12);
    addstr("* 48 x 32 monochrome display per VMU");
    move(18, 12);
    addstr("* 128 Kbyte non-volatile memory per VMU");
    move(19, 12);
    addstr("* 104 key keyboard");
    move(20, 12);
    addstr("* 3-button scrolling mouse");
    move(21, 12);
    addstr("* Microphone");
}

static void
slide6(void) {
    move(2, 2);
    addstr("For a CD-R to be bootable, it needs two sessions:");
    move(3, 4);
    addstr("1st session contains an audio track. Silence is fine.");
    move(4, 4);
    addstr("2nd session contains a data track with an ISO9660 file system.");

    move(6, 2);
    addstr("The 1st 16 sectors of the data track must contain a bootstrap consisting of:");
    move(7, 4);
    addstr("1. Metadata info (required peripherals, boot binary filename, etc)");
    move(8, 4);
    addstr("2. Table of contents (can be filled with 0s)");
    move(9, 4);
    addstr("3. SEGA license screen code (required)");
    move(10, 4);
    addstr("4. Region protection symbols (required)");
    move(11, 4);
    addstr("5. Bootstrap 1 - Sets up hardware registers, transfers to bootstrap 2");
    move(12, 4);
    addstr("6. Bootstrap 2 - Transfers control to the boot binary file");

    move(14, 2);
    addstr("The SEGA license code in section 3 can NOT be modified. The ROM checks");
    move(15, 2);
    addstr("every byte of section 3 against a copy in the ROM, and will not boot the");
    move(16, 2);
    addstr("disk if there is anything other than the text:");

    attron(COLOR_PAIR(5) | A_BOLD);
    center(18, "\"PRODUCED BY OR UNDER LICENSE FROM SEGA ENTERPRISES, LTD.\"");
    attroff(COLOR_PAIR(5) | A_BOLD);

    move(20, 2);
    addstr("The boot binary is loaded into memory right after the first 16 sectors");
    move(21, 2);
    addstr("and the boot binary then loads the NetBSD kernel.");

    move(23, 2);
    addstr("An interresting feature of the bootloader is that for normal CD-ROMSs");
    move(24, 2);
    addstr("(but not GD-ROMS) the boot binary file is loaded in a pseudo-random manner.");
    move(25, 2);
    addstr("In order for your boot binary file to be loaded it has to be \"scrambled\"");
}

static void
slide7(void) {
    move(2, 2);
    attron(A_UNDERLINE);
    addstr("Obtain the Source:");
    attroff(A_UNDERLINE);
    move(3, 4);
    attron(COLOR_PAIR(4));
    addstr("# export CVSROOT=\"anoncvs@anoncvs.NetBSD.org:/cvsroot\"");
    move(4, 4);
    addstr("# cvs checkout -r netbsd-7 -P src");
    move(5, 4);
    addstr("# cvs checkout -r netbsd-7 -P xsrc");
    attroff(COLOR_PAIR(4));

    move(7, 2);
    attron(A_UNDERLINE);
    addstr("build.sh");
    attroff(A_UNDERLINE);
    move(8, 2);
    addstr("NetBSD comes with a build tool that handles all the details of building");
    move(9, 2);
    addstr("a cross-compiling toolschain and then using that toolchain to build a ");
    move(10, 2);
    addstr("target kernel and userland.");

    move(12, 2);
    attron(A_UNDERLINE);
    addstr("Build the tools:");
    attroff(A_UNDERLINE);
    move(13, 4);
    attron(COLOR_PAIR(4));
    addstr("# build.sh -O /tmp/obj -T /tmp/tools -j 8 -U -m dreamcast tools");
    attroff(COLOR_PAIR(4));

    move(15, 2);
    attron(A_UNDERLINE);
    addstr("Optionally, customize and build a kernel");
    attroff(A_UNDERLINE);
    move(16, 4);
    attron(COLOR_PAIR(4));
    addstr("# build.sh -O /tmp/obj -T /tmp/tools -j 8 -U -m dreamcast kernel=GENERIC ");
    attroff(COLOR_PAIR(4));

    move(18, 2);
    attron(A_UNDERLINE);
    addstr("Perform a full build and release");
    attroff(A_UNDERLINE);
    move(19, 4);
    attron(COLOR_PAIR(4));
    addstr("# build.sh -O /tmp/obj -T /tmp/tools -j 8 -U -m dreamcast build");
    move(20, 4);
    addstr("# build.sh -O /tmp/obj -T /tmp/tools -j 8 -U -m dreamcast release");
    attroff(COLOR_PAIR(4));

    move(22, 2);
    attron(A_UNDERLINE);
    addstr("Build the sets (gzipped tar files with build artifacts)");
    attroff(A_UNDERLINE);
    move(23, 4);
    attron(COLOR_PAIR(4));
    addstr("# build.sh -O /tmp/obj -T /tmp/tools -j 8 -U -m dreamcast sets");
    attroff(COLOR_PAIR(4));

    center(25, "A full build starting with tools takes about 50min on a dual socket");
    center(26, "2.3Ghz Quad-Core 2350 AMD Opteron Processor with a SanDisk SSD");

    attron(A_BOLD);
    center(28, "P.S. Thank you Sean for the build hardware!");
    attroff(A_BOLD);
}

static void
slide8 (void) {
    move(3, 2);
    attron(A_UNDERLINE);
    addstr("Creating a custom set for custom scripts");
    attroff(A_UNDERLINE);
    move(4, 2);
    addstr("The following will create a set that will be extracted to /opt");
    move(5, 4);
    attron(COLOR_PAIR(4));
    addstr("# BIN_DIR=/tmp/obj/releasedir/dreamcast/binary");
    move(6, 4);
    addstr("# tar -czf $BIN_DIR/sets/opt.tgz /home/tpaul/opt");
    attroff(COLOR_PAIR(4));

    move(8, 2);
    attron(A_UNDERLINE);
    addstr("Burn the CD-ROM");
    attroff(A_UNDERLINE);
    move(9, 2);
    addstr("dc-burn-netbsd handles creating the audio track, ISO9660 filesystem, and");
    move(10, 2);
    addstr("scrambled binary boot file and then burns it to disc.");
    move(11, 4);
    attron(COLOR_PAIR(4));
    addstr("# SETS='base.tgz etc.tgz games.tgz man.tgz opt.tgz'");
    move(12, 4);
    addstr("# dc-burn-netbsd -v 7.0 -C -b -d $BIN_DIR -k GENERIC -l -s $SETS");
    attroff(COLOR_PAIR(4));

    attron(A_BOLD);
    center(14, "Now you should have a CD-ROM that can be booted by the Dreamcast!");
    attroff(A_BOLD);

    attron(COLOR_PAIR(2));
    center(18, "                                    ________     ");
    center(19, "  Who wants to play video games?  ||        ||   ");
    center(20, "                                  || .   .  ||   ");
    center(21, " _|_|_|    _|      _|    _|_|     ||    -   ||   ");
    center(22, " _|    _|  _|_|  _|_|  _|    _| \\/||--------||\\/ ");
    center(23, " _|_|_|    _|  _|  _|  _|    _|   ||===   . ||   ");
    center(24, " _|    _|  _|      _|  _|    _|   || +  o  0||   ");
    center(25, " _|_|_|    _|      _|    _|_|     ||________||   ");
    center(26, "                                     |    |      ");
    attroff(COLOR_PAIR(2));
    move(29, 38);
    addstr("ascii art by brandtamos @ bit.ly/1RNMNVi");
}

static void
slide9 (void) {
    move(2, 2);
    addstr("Customizing the CD-ROM is pretty easy. I simply wrote a curses program");
    move(3, 2);
    addstr("for this presentation and added it to the source tree.");

    move(5, 2);
    addstr("Since this presentation is for the Dreamcast I decided to put it");
    move(6, 2);
    addstr("into the games directory:");

    attron(COLOR_PAIR(2));
    move(8, 2);
    addstr("file: /cvsroot/src/games/Makefile,v");
    move(9, 2);
    addstr("17c17");
    move(10, 2);
    attron(COLOR_PAIR(5));
    addstr("<       wargames worm worms wtf wump");
    move(11, 2);
    addstr("---");
    move(12, 2);
    attroff(COLOR_PAIR(5));
    attron(COLOR_PAIR(4));
    addstr(">       wargames worm worms wtf wump fwbug1");
    attroff(COLOR_PAIR(4));
    attroff(COLOR_PAIR(2));

    move(14, 2);
    addstr("I then put my main.c into games/fwbug1 and created the following Makefile:");
    attron(COLOR_PAIR(2));
    move(16, 2);
    addstr("PROG=   fwbug1");
    move(17, 2);
    addstr("SRCS=   main.c ");
    move(18, 2);
    addstr("DPADD=  ${LIBCURSES}");
    move(19, 2);
    addstr("LDADD=  -lcurses");
    move(20, 2);
    addstr(".include <bsd.prog.mk>");
    attroff(COLOR_PAIR(2));

    move(22, 2);
    addstr("Last step was to update distrib/sets/lists/games/mi so that the");
    move(23, 2);
    addstr("binary gets into the set:");

    attron(COLOR_PAIR(2));
    move(25, 2);
    addstr("file: /cvsroot/src/distrib/sets/lists/games/mi,v");
    move(26, 2);
    addstr("27a28");
    move(27, 2);
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(4));
    addstr("> ./usr/games/fwbug1 games-utils-bin");
    attroff(COLOR_PAIR(4));
}

static void
slide10 (void) {
    move(10, 6);
    attron(A_UNDERLINE);
    addstr("Future Improvemnts");
    attroff(A_UNDERLINE);
    move(11, 8);
    addstr("* Swap over NFS");
    move(12, 8);
    addstr("* Read/write VMU memory and screen");
    move(13, 8);
    addstr("* Use mouse in terminal (update console drivers)");
    move(14, 8);
    addstr("* Use puru puru pack for terminal bell");
    move(15, 8);
    addstr("* kernel tuning - trim out uneeded features");
    move(16, 8);
    addstr("* Read and use controller input");
    move(17, 8);
    addstr("* Get X11 Working");
    move(18, 8);
    addstr("* Netboot kernel via IPSlave");
    move(19, 8);
    addstr("* Audio input/output");
    move(20, 8);
    addstr("* dc-burn-netbsd improvements");
    move(21, 8);
    addstr("* Get current branch working");
    move(22, 8);
    addstr("* Recover from IO errors");


}

static void
slide11 (void) {
    attron(COLOR_PAIR(2));  
    center(10, " ________             __        __");
    center(11, "/_  __/ /  ___ ____  / /__ ___ / /");
    center(12, " / / / _ \\/ _ `/ _ \\/  '_/(_-</_/ ");
    center(13, "/_/ /_//_/\\_,_/_//_/_/\\_\\/___(_)  ");
    attroff(COLOR_PAIR(2));  

    attron(A_BOLD);                                  
    center(15, "Github: TravisPaul");
    center(16, "Email: Tr@visPaul.me");
    center(17, "#netbsd/#pkgsrc: tpaul");
    attroff(A_BOLD);      
}

int
main (int argc, char **argv) {
    char key;
    int current;
    int skip = 0;

    win = initscr();
    resizeterm(ROWS, COLS);
    cbreak();
    noecho();
    start_color();
    clear();

    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);

    strcpy(slides[0].title, "FWBUG Meetup #1");
    slides[0].slide = slide1;

    strcpy(slides[1].title, "Fort Wayne BSD User Group");
    slides[1].slide = slide2;

    strcpy(slides[2].title, "NetBSD");
    slides[2].slide = slide3a;

    strcpy(slides[3].title, "What is NetBSD?");
    slides[3].slide = slide3b;

    strcpy(slides[4].title, "Dreamcast History");
    slides[4].slide = slide4;

    strcpy(slides[5].title, "Dreamcast Hardware");
    slides[5].slide = slide5;

    strcpy(slides[6].title, "Booting the Dreamcast");
    slides[6].slide = slide6;

    strcpy(slides[7].title, "Cross-compiling with build.sh");
    slides[7].slide = slide7;

    strcpy(slides[8].title, "Burning the CD-ROM");
    slides[8].slide = slide8;

    strcpy(slides[9].title, "Customizing the build");
    slides[9].slide = slide9;

    strcpy(slides[10].title, "Future Improvements");
    slides[10].slide = slide10;

    strcpy(slides[11].title, "Outro");
    slides[11].slide = slide11;

    if (argc > 1) {
        current = (int) strtol(argv[1], (char **)NULL, 10) - 1;
    } else {
        current = 0;
    }

    template(current);

    while (key != 'q') {
        key = getch();
        switch (key) {
            case 't':
                toc();
                skip = 1;
            break;
            case 'l':
            case 'C':
                current += 1;
            break;
            case 'h':
            case 'D':
                current -= 1;
            break;
            case 'k':
            case 'A':
                current = 0;
            break;
            case 'j':
            case 'B':
                current = SLIDES - 1;
            break;
        }

        if (!skip) {
            template(current);
        } else {
            skip = 0;
        }
    }   
    endwin();
    return 0;
}
