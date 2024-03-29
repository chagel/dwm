/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 20, .gappx = 20};
static const unsigned int snap      = 30;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { 
  "xos4 Terminess Powerline:style:Bold:size=7",
  "Cantarell:size=7", 
  "Hiragino Sans GB W3:size=7", 
  "FontAwesome:size=8",
};
static const char col_gray1[]       = "#000000";
static const char col_gray2[]       = "#20212b";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#000000";
//static const char col_high[]        = "#BD93F9";
static const char col_high[]        = "#666666";
static const unsigned int baralpha  = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_high  },
};

static const unsigned int alphas[][3] = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered     isfloating   monitor */
  { "feh",      NULL,       NULL,       0,            1,             1,           -1 },
  { "surf",     NULL,       NULL,       0,            1,             1,           -1 },
  { "st",       "",         "",         0,            False,         False,       -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
  { "TTT",      bstack },
	{ "===",      bstackhoriz },
};

/* key definitions */
#define MODKEY Mod4Mask // Mod1Mask for alt, Mod4Mask for WinKey
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", "less", "/home/mike/.scratch.note", NULL };

static Key keys[] = {
	/* modifier                     key                         function        argument */
  { MODKEY,                       XK_grave,                   togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,                       togglebar,      {0} },
	{ MODKEY,                       XK_j,                       focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                       focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,                       focusstack,     {.i = -1} },
	{ MODKEY,                       XK_l,                       focusstack,     {.i = +1} },
	{ MODKEY,                       XK_minus,                   setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,                   setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,                   setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,                   setgaps,        {.i = GAP_TOGGLE} },
	{ MODKEY|ShiftMask,             XK_h,                       setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,                       setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,                       setcfact,       {.f = -0.25} },
  { MODKEY|ShiftMask,             XK_k,                       setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_o,                       setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_i,                       incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                       incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_z,                       zoom,           {0} },
	{ MODKEY,                       XK_Tab,                     view,           {0} },
	{ MODKEY,                       XK_q,                       killclient,     {0} },
	{ MODKEY,                       XK_t,                       setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                       setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                       setlayout,      {.v = &layouts[2]} },
  { MODKEY,                       XK_u,                       setlayout,      {.v = &layouts[3]} },
  { MODKEY|ShiftMask,             XK_u,                       setlayout,      {.v = &layouts[4]} },
  { MODKEY,                       XK_y,                       setlayout,      {.v = &layouts[5]} },
  { MODKEY|ShiftMask,             XK_y,                       setlayout,      {.v = &layouts[6]} },
  { MODKEY|ShiftMask,             XK_f,                       fullscreen,     {0} },
  { MODKEY,                       XK_r,                       resetlayout,    {0} },
	{ MODKEY|ShiftMask,             XK_space,                   togglefloating, {0} },
  { MODKEY,                       XK_Down,                    moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,                      moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,                   moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,                    moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,                    moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,                      moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,                   moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,                    moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,                      moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,                    moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,                    moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,                   moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,                      moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,                    moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,                    moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,                   moveresizeedge, {.v = "R"} },
	{ MODKEY,                       XK_0,                       view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                       tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                  tagmon,         {.i = +1 } },
  { MODKEY,                       XK_bracketright,            shiftview,      {.i = +1 } },
	{ MODKEY,                       XK_bracketleft,             shiftview,      {.i = -1 } },
	TAGKEYS(                        XK_1,                                       0)
	TAGKEYS(                        XK_2,                                       1)
	TAGKEYS(                        XK_3,                                       2)
	TAGKEYS(                        XK_4,                                       3)
	TAGKEYS(                        XK_5,                                       4)
	TAGKEYS(                        XK_6,                                       5)
	TAGKEYS(                        XK_7,                                       6)
	TAGKEYS(                        XK_8,                                       7)
	TAGKEYS(                        XK_9,                                       8)
  { Mod1Mask|ControlMask|ShiftMask, XK_Left,                    toggleleft,     {0} },
  { Mod1Mask|ControlMask|ShiftMask, XK_Right,                   toggleright,    {0} },
  { Mod1Mask|ControlMask|ShiftMask, XK_Down,                    togglebottom,   {0} },
  { Mod1Mask|ControlMask|ShiftMask, XK_Up,                      toggletop,      {0} },
  { Mod1Mask|ControlMask|ShiftMask, XK_c,                       togglecenter,   {0} },
  { Mod1Mask|ControlMask|ShiftMask, XK_m,                       togglemaximize, {0} },
	{ Mod1Mask|ControlMask|ShiftMask, XK_q,                       quit,         {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

