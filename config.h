/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrains Mono:size=10" };
static const char dmenufont[]       = "Jetbrains Mono:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#008080";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "pcmanfm",  NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[@]",      spiral },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "urxvt", NULL };

#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       33,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       185,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             36, 	 spawn,          {.v = termcmd } },
	{ MODKEY,                       56,      togglebar,      {0} },
	{ MODKEY,                       246,      togglebar,      {0} },
	{ MODKEY,                       44,      focusstack,     {.i = +1 } },
	{ MODKEY,                       226,      focusstack,     {.i = +1 } },
	{ MODKEY,                       45,      focusstack,     {.i = -1 } },
	{ MODKEY,                       227,      focusstack,     {.i = -1 } },
	{ MODKEY,                       31,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       183,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       40,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       220,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       43,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       224,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       46,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       228,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       36,	 zoom,           {0} },
	{ MODKEY,                       23,    	 view,           {0} },
	{ MODKEY|ShiftMask,             54,      killclient,     {0} },
	{ MODKEY|ShiftMask,             235,      killclient,     {0} },
	{ MODKEY,                       24,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       161,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       25,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       162,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       26,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       168,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       27,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       170,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       65,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             65,  togglefloating, {0} },
	{ MODKEY,                       19,      view,           {.ui = ~0 } },
	{ MODKEY,                       155,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             19,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             155,      tag,            {.ui = ~0 } },
	{ MODKEY,                       59,  focusmon,       {.i = -1 } },
	{ MODKEY,                       251,  focusmon,       {.i = -1 } },
	{ MODKEY,                       60, focusmon,       {.i = +1 } },
	{ MODKEY,                       252, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             59,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             251,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             60, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             252, tagmon,         {.i = +1 } },
	{ MODKEY,                       20,  setgaps,        {.i = -1 } },
	{ MODKEY,                       159,  setgaps,        {.i = -1 } },
	{ MODKEY,                       21,  setgaps,        {.i = +1 } },
	{ MODKEY,                       160,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             21,  setgaps,        {.i = 0  } },
	{ MODKEY|ShiftMask,             160,  setgaps,        {.i = 0  } },
	{ MODKEY,                       53,  	   shiftview,      {.i = -1 } },
	{ MODKEY,                       234,  	   shiftview,      {.i = -1 } },
	{ MODKEY,                       54,  	   shiftview,      {.i = +1 } },
	{ MODKEY,                       235,  	   shiftview,      {.i = +1 } },	
	{ MODKEY|ShiftMask,             41,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             221,      togglefullscr,  {0} },
	{ MODKEY,							  111,	   spawn,	   SHCMD("amixer-louder")},
	{ MODKEY,							  116,   spawn,	   SHCMD("amixer-quieter")},
	{ MODKEY,                       75,	   spawn,          SHCMD("setlayout-dvorakqw") },
	{ MODKEY,							  76,	   spawn,	   SHCMD("setlayout-dvorak") },
	{ MODKEY,                       95,    spawn,          SHCMD("setlayout-qwerty") },
	{ MODKEY,                       71,	   spawn,          SHCMD("darker") },
	{ MODKEY,                       72,     spawn,          SHCMD("brighter") },
	TAGKEYS(                        10,                      0)
	TAGKEYS(                        131,                      0)
	TAGKEYS(                        11,                      1)
	TAGKEYS(                        109,                      1)
	TAGKEYS(                        12,                      2)
	TAGKEYS(                        138,                      2)
	TAGKEYS(                        13,                      3)
	TAGKEYS(                        140,                      3)
	TAGKEYS(                        14,                      4)
	TAGKEYS(                        120,                      4)
	TAGKEYS(                        15,                      5)
	TAGKEYS(                        128,                      5)
	TAGKEYS(                        16,                      6)
	TAGKEYS(                        147,                      6)
	TAGKEYS(                        17,                      7)
	TAGKEYS(                        149,                      7)
	TAGKEYS(                        18,                      8)
	TAGKEYS(                        154,                      8)
	{ MODKEY|ShiftMask,             24,      quit,           {0} },
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
