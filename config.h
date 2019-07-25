/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=18" };
/* static const char *fonts[]          = { "System San Francisco Display:size=18" }; */
static const char dmenufont[]       = "monospace:size=18";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_orange[]      = "#c25704";
static const char col_orange2[]     = "#c25704";
static const char col_black[]       = "#000000";
static const char col_red[]         = "#ff0000";
static const char col_yellow[]      = "#ffff00";
static const char col_white[]       = "#ffffff";
static const char col_yellow2[]     = "#b29f27";
static const char col_blue2[]       = "#61AEEE";
static const char col_pink[]        = "#F79494";
static const char col_green[]       = "#98C379";
static const char col_yellow3[]     = "#c0c000";

static const char *colors[][3]      = {
	/*                      fg                  bg              border    */
	[SchemeNorm]        =   { col_orange2,      col_gray1,      col_gray2  },
	[SchemeSel]         =   { col_gray4,        col_orange,     col_orange },
	[SchemeTitle]       =   { col_orange2,      col_gray1,      col_gray2  },
	[SchemeWarn]        =   { col_black,        col_yellow,     col_gray2  },
	[SchemeUrgent]      =   { col_white,        col_red,        col_gray2  },
	[5]                 =   { col_yellow2,      col_gray1,      col_gray2  },
	[6]                 =   { col_blue2,        col_gray1,      col_gray2  },
	[7]                 =   { col_pink,         col_gray1,      col_gray2  },
	[8]                 =   { col_yellow3,      col_gray1,      col_gray2  },
};


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscenterd   isfloating  monitor */
	{ "mpv",      NULL,       NULL,       1 << 10,       0,          0,          -1 },
	{ "newsboat", NULL,       NULL,       1 << 11,      0,          0,          -1 },
	{ "htop",     NULL,       NULL,       1 << 12,      0,          0,          -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      comboview,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      combotag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_orange, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier           key             function        argument */
	{ MODKEY,             XK_b,           togglebar,      {0} },
	{ MODKEY,             XK_j,           focusstack,     {.i = -1 } },
	{ MODKEY,             XK_Left,        focusstack,     {.i = -1 } },
	{ MODKEY,             XK_k,           focusstack,     {.i = +1 } },
	{ MODKEY,             XK_Right,       focusstack,     {.i = +1 } },
	{ MODKEY,             XK_i,           incnmaster,     {.i = +1 } },
	{ MODKEY,             XK_d,           incnmaster,     {.i = -1 } },
	{ MODKEY,             XK_h,           setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,   XK_Left,        setmfact,       {.f = -0.05} },
	{ MODKEY,             XK_l,           setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,   XK_Right,       setmfact,       {.f = +0.05} },
	{ MODKEY,             XK_Tab,         view,           {0} },
	{ MODKEY,             XK_q,           killclient,     {0} },
	{ MODKEY,             XK_numbersign,  setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,   XK_numbersign,  setlayout,      {.v = &layouts[1]} },
	{ MODKEY,             XK_f,           setlayout,      {.v = &layouts[2]} },
	{ MODKEY,             XK_space,       setlayout,      {0} },
	{ MODKEY|ShiftMask,   XK_space,       togglefloating, {0} },
	{ MODKEY|ShiftMask,   XK_a,           view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,   XK_z,           tag,            {.ui = ~0 } },
	{ MODKEY,             XK_comma,       focusmon,       {.i = -1 } },
	{ MODKEY,             XK_period,      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,   XK_comma,       tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,   XK_period,      tagmon,         {.i = +1 } },
	TAGKEYS(              XK_1,                           0)
	TAGKEYS(              XK_2,                           1)
	TAGKEYS(              XK_3,                           2)
	TAGKEYS(              XK_4,                           3)
	TAGKEYS(              XK_5,                           4)
	TAGKEYS(              XK_6,                           5)
	TAGKEYS(              XK_7,                           6)
	TAGKEYS(              XK_8,                           7)
	TAGKEYS(              XK_9,                           8)
	TAGKEYS(              XK_0,                           9)
	TAGKEYS(              XK_v,                           10)
	TAGKEYS(              XK_n,                           11)
	TAGKEYS(              XK_t,                           12)
	{ MODKEY|ShiftMask,   XK_x,           quit,          {0} },
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
	{ ClkClientWin,         MODKEY,         Button3,        killclient,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

