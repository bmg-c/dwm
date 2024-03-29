/* See LICENSE file for copyright and license details. */

#include "base16.h"

/* appearance */
static const unsigned int borderpx    = 0;          /* border pixel of windows */
static const unsigned int gappx       = 20;         /* gaps between windows */
static const unsigned int snap        = 10;         /* snap pixel */
static const int showbar              = 1;          /* 0 means no bar */
static const int topbar               = 1;          /* 0 means bottom bar */
static const unsigned int barheight   = gappx + 30; /* height of bar */
static const char *fonts[]            = { "RobotoMono Nerd Font:size=12" };
static const Base16Colors base16theme = base16gruvboxdarkmedium;
static const char *colors[][3]        = {
	/*               fg                  bg                  border */
	[SchemeNorm] = { base16theme.base05, base16theme.base00, base16theme.base00 },
	[SchemeSel]  = { base16theme.base07, base16theme.base01, base16theme.base07 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class  instance  title  tags mask  iscentered,  isfloating  monitor */
	{ NULL,   NULL,     NULL,  0,         0,           0,          -1 },
	{ "firefox",   "Navigator",     NULL,  1 << 1,         0,           0,          -1 },
	{ "Pcmanfm",   "pcmanfm",     NULL,  0,         1,           1,          -1 },
	{ "MuPDF",   "mupdf",     NULL,  0,         1,           1,          -1 },
	{ "YouTube Music",   "youtube music",     NULL,  1 << 3,         0,           0,          -1 },
	{ "discord",   "discord",     NULL,  1 << 4,         0,           0,          -1 },
	{ "easyeffects",   "easyeffects",     NULL,  1 << 8,         0,           0,          -1 },
	{ "Steam",   "Steam",     NULL,  1 << 7,         0,           0,          -1 },
	{ NULL,   NULL,     "Steam",  1 << 7,         1,           0,          -1 },
	{ "PrismLauncher",   "prismlauncher",     NULL,  1 << 7,         0,           0,          -1 },
	{ "TelegramDesktop",   "telegram-desktop",     NULL,  1 << 4,         0,           0,          -1 },
};

/* layout(s) */
static const float mfact     = 0.6; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "Tile",     tile },    /* first entry is default */
	{ "Float",    NULL },    /* no layout function means floating behavior */
	{ "Mono",     monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
        { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
        { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
// #define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { /* requires custom build of dmenu */
	"dmenu_run",
	"-c",
	"-l",  "5",
	"-h",  "40",
	"-bw", "60",
	"-fn", "Source Sans Pro:size=12",
	"-m",  dmenumon,
	"-nb", base16theme.base01,
	"-nf", base16theme.base05,
	"-sb", base16theme.base02,
	"-sf", base16theme.base07,
	"-bc", base16theme.base01,
	NULL
};

static const char *termcmd[]  	 = 	{ "st", NULL };

static const char *volup[] 	 = 	{ "amixer", "set", "Master", "5%+", NULL };
static const char *voldown[] 	 = 	{ "amixer", "set", "Master", "5%-", NULL };

static const char *brightup[] 	 = 	{ "brightnessctl", "set", "+15", NULL };
static const char *brightdown[]  = 	{ "brightnessctl", "set", "15-", NULL };
static const char *brightdef[] 	 = 	{ "brightnessctl", "set", "180", NULL };

static const char *screenshot[]  = 	{ "flameshot", "gui", NULL };

static const char *wpchange[]	 =	{ "wpchange", NULL };
static const char *hornywpchange[] =    { "wpchange", "-h", NULL };

static const char *setkblayout[] = 	{ "setkblayout", "-rofi", "us:,ru:", "us:engram-qwerty,us:russian-qwerty", NULL };

static const char *startscreen[] = { "startscreen", NULL };

static Key keys[] = {
	/* modifier                     key	function        argument */
        { MODKEY,                       33,	spawn,          {.v = dmenucmd } },
        { MODKEY,                       185,	spawn,          {.v = dmenucmd } },
        { MODKEY|ShiftMask,             36,	spawn,          {.v = termcmd } },
        { MODKEY,                       56,	togglebar,      {0} },
        { MODKEY,                       246,	togglebar,      {0} },
        { MODKEY,                       44,	focusstack,     {.i = +1 } },
        { MODKEY,                       226,	focusstack,     {.i = +1 } },
        { MODKEY,                       45,	focusstack,     {.i = -1 } },
        { MODKEY,                       227,	focusstack,     {.i = -1 } },
        { MODKEY,                       31,	incnmaster,     {.i = +1 } },
        { MODKEY,                       183,	incnmaster,     {.i = +1 } },
        { MODKEY,                       40,	incnmaster,     {.i = -1 } },
        { MODKEY,                       220,	incnmaster,     {.i = -1 } },
        { MODKEY,                       43,	setmfact,       {.f = -0.05} },
        { MODKEY,                       224,	setmfact,       {.f = -0.05} },
        { MODKEY,                       46,	setmfact,       {.f = +0.05} },
        { MODKEY,                       228,	setmfact,       {.f = +0.05} },
        { MODKEY,                       36,	zoom,           {0} },
        { MODKEY|ShiftMask,             54,	killclient,     {0} },
        { MODKEY|ShiftMask,             235,	killclient,     {0} },
        { MODKEY,                       24,	setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       161,	setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       25,	setlayout,      {.v = &layouts[1]} },
        { MODKEY,                       162,	setlayout,      {.v = &layouts[1]} },
        { MODKEY,                       26,	setlayout,      {.v = &layouts[2]} },
        { MODKEY,                       168,	setlayout,      {.v = &layouts[2]} },
        { MODKEY,                       27,	setlayout,      {.v = &layouts[3]} },
        { MODKEY,                       170,	setlayout,      {.v = &layouts[3]} },
        { MODKEY,                       65,	setlayout,      {0} },
        { MODKEY|ShiftMask,             65,	togglefloating, {0} },
        { MODKEY,                       19,	view,           {.ui = ~0 } },
        { MODKEY,                       155,	view,           {.ui = ~0 } },
        { MODKEY|ShiftMask,             19,	tag,            {.ui = ~0 } },
        { MODKEY|ShiftMask,             155,	tag,            {.ui = ~0 } },
        { MODKEY,                       59,	focusmon,       {.i = -1 } },
        { MODKEY,                       251,	focusmon,       {.i = -1 } },
        { MODKEY,                       60,	focusmon,       {.i = +1 } },
        { MODKEY,                       252,	focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,             59,	tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,             251,	tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,             60,	tagmon,         {.i = +1 } },
        { MODKEY|ShiftMask,             252,	tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             41,	togglefullscr,  {0} }, 				// Shift-F. Fullscreen
        { MODKEY|ShiftMask,             221,	togglefullscr,  {0} }, 				
	{ MODKEY,                       111,	spawn,		{ .v = volup } }, 		// UpArrow. Louder
        { MODKEY,                       116,	spawn,		{ .v = voldown } }, 		// DownArrow. Quiter
	{ MODKEY|ShiftMask,		219,	spawn,          { .v = screenshot } },		// Shift-S. Screenshot
	
	{ MODKEY,                       71,	spawn,          { .v = brightdown } },		// F6. Darker
	{ MODKEY,                       232,	spawn,          { .v = brightdown } },
        { MODKEY,                       72,	spawn,          { .v = brightup } },		// F5. Brighter
	{ MODKEY,                       233,	spawn,          { .v = brightup } },
	{ MODKEY,                       67,	spawn,          { .v = brightdef } },		// F1. Standard brightness
	{ MODKEY,                       121,	spawn,          { .v = brightdef } },

	{ MODKEY,			96,	spawn,		{ .v = wpchange } },		// F12.	Randomize wallpaper
	{ MODKEY|ShiftMask, 		96,     spawn,          { .v = hornywpchange } },       // Shift-F12. Randomize horny wallpaper

        { MODKEY,                       95,     spawn,          { .v = setkblayout } }, 	// F11. Set Keyboard Layout
    { MODKEY,                       73,         spawn,           { .v = startscreen } },

	TAGKEYS(                        10,                     0)
        TAGKEYS(                        131,                    0)
        TAGKEYS(                        11,                     1)
        TAGKEYS(                        109,                    1)
        TAGKEYS(                        12,                     2)
        TAGKEYS(                        138,                    2)
        TAGKEYS(                        13,                     3)
        TAGKEYS(                        140,                    3)
        TAGKEYS(                        14,                     4)
        TAGKEYS(                        120,                    4)
        TAGKEYS(                        15,                     5)
        TAGKEYS(                        128,                    5)
        TAGKEYS(                        16,                     6)
        TAGKEYS(                        147,                    6)
        TAGKEYS(                        17,                     7)
        TAGKEYS(                        149,                    7)
        TAGKEYS(                        18,                     8)
        TAGKEYS(                        154,                    8)
        { MODKEY|ShiftMask,             24,	quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
	IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
	IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
	IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
	IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
	IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
	IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
	IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
	IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
	IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
	IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
	IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
	IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
	IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
	IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};

static const char startup[] = "$HOME/scripts/startup.sh";
