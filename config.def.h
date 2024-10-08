/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 5;        /* 2 is the default spacing around the bar's font */
static const char buttonbar[]       = " ";
#define ICONSIZE					(bh - 4)   /* icon size */
#define ICONSPACING					10 /* space between icon and title */
static const char *fonts[]          = { "Noto Sans:style=Medium:size=14",
										"FiraMono Nerd Font:size=16",
										"FiraMono Nerd Font:style=Bold:size=12" };
static const char dmenufont[]       = "Noto Sans:size=15";

#include "termcolors.h"

static char normfgcolor[]			= "#bbbbbb";
static char normbgcolor[]			= "#222222";
static char normbordercolor[]		= "#444444";
static char normfloatcolor[]		= "#444444";

static char selfgcolor[]			= "#eeeeee";
static char selbgcolor[]			= "#005577";
static char selbordercolor[]		= "#61afef";
static char selfloatcolor[]			= "#c678dd";

static char stickyfgcolor[]			= "#bbbbbb";
static char stickybgcolor[]			= "#222222";
static char stickybordercolor[]		= "#ffdd00";
static char stickyfloatcolor[]		= "#ffdd00";

static char scratchnormfgcolor[]	= "#bbbbbb";
static char scratchnormbgcolor[]	= "#222222";
static char scratchnormbordercolor[] = "#444444";
static char scratchnormfloatcolor[]	= "#444444";

static char scratchselfgcolor[]		= "#bbbbbb";
static char scratchselbgcolor[]		= "#222222";
static char scratchselbordercolor[]	= "#ff5555";
static char scratchselfloatcolor[]	= "#ff5555";

static char stbuttonfgcolor[]		= "#61afef";
static char stbuttonbgcolor[]		= "#222222";
static char stbuttonbordercolor[]	= "#000000";
static char stbuttonfloatcolor[]	= "#000000";

static char ltsymbolfgcolor[]		= "#ffdd00";
static char ltsymbolbgcolor[]		= "#222222";
static char ltsymbolbordercolor[]	= "#000000";
static char ltsymbolfloatcolor[]	= "#000000";

static char tagsnormfgcolor[]		= "#666666";
static char tagsnormbgcolor[]		= "#222222";
static char tagsnormbordercolor[]	= "#000000";
static char tagsnormfloatcolor[]	= "#000000";

static char tagsoccfgcolor[]		= "#aaaaaa";
static char tagsoccbgcolor[]		= "#222222";
static char tagsoccbordercolor[]	= "#000000";
static char tagsoccfloatcolor[]		= "#000000";

static char tagsselfgcolor[]		= "#eeeeee";
static char tagsselbgcolor[]		= "#005577";
static char tagsselbordercolor[]	= "#000000";
static char tagsselfloatcolor[]		= "#000000";

static char *colors[][4]      = {
	/*               		fg           bg         border   */
	[SchemeNorm] 		= { normfgcolor,		normbgcolor,		normbordercolor, 		normfloatcolor     },
	[SchemeSel] 		= { selfgcolor,			selbgcolor,			selbordercolor, 		selfloatcolor      },
	[SchemeSticky] 		= { stickyfgcolor,		stickybgcolor,		stickybordercolor, 		stickyfloatcolor   },
	[SchemeScratchNorm] = { scratchnormfgcolor,	scratchnormbgcolor,	scratchnormbordercolor,	scratchnormfloatcolor   },
	[SchemeScratchSel]  = { scratchselfgcolor,	scratchselbgcolor,	scratchselbordercolor, 	scratchselfloatcolor   },
	[SchemeStButton] 	= { stbuttonfgcolor,	stbuttonbgcolor,	stbuttonbordercolor, 	stbuttonfloatcolor },
	[SchemeLtSymbol] 	= { ltsymbolfgcolor,	ltsymbolbgcolor,	ltsymbolbordercolor,	ltsymbolfloatcolor },
	[SchemeTagsNorm] 	= { tagsnormfgcolor,	tagsnormbgcolor,	tagsnormbordercolor, 	tagsnormfloatcolor },
	[SchemeTagsOcc] 	= { tagsoccfgcolor,		tagsoccbgcolor,		tagsoccbordercolor,		tagsoccfloatcolor  },
	[SchemeTagsSel] 	= { tagsselfgcolor,		tagsselbgcolor,		tagsselbordercolor,		tagsselfloatcolor  },
};


static const XPoint stickyicon[]    = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb    = {4,8};	/* defines the bottom right corner of the polygon's bounding box (speeds up scaling) */

static const unsigned int baralpha = 0xb1;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int alphas[][4]      = {
    [SchemeNorm] 		= { OPAQUE, baralpha, borderalpha, borderalpha },
	[SchemeSel]  		= { OPAQUE, baralpha, borderalpha, borderalpha },
	[SchemeSticky]  	= { OPAQUE, baralpha, borderalpha, borderalpha },
	[SchemeScratchNorm] = { OPAQUE, baralpha, borderalpha, borderalpha },
	[SchemeScratchSel]  = { OPAQUE, baralpha, borderalpha, borderalpha },
	[SchemeLtSymbol]  	= { OPAQUE, baralpha, borderalpha, borderalpha },
	[SchemeStButton]  	= { OPAQUE, baralpha, borderalpha, borderalpha },
    [SchemeTagsNorm] 	= { OPAQUE, baralpha, borderalpha, borderalpha },
    [SchemeTagsOcc] 	= { OPAQUE, baralpha, borderalpha, borderalpha },
    [SchemeTagsSel] 	= { OPAQUE, OPAQUE,   borderalpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	{ .class = "Lxappearance", .isfloating = 1, .floatpos = "50% 50% -1w -1h" },
	{ .class = "St", .tags = 1 << 0, .isterminal = 1 },
	{ .class = "firefox", .tags = 1 << 1 },
	{ .class = "Thunar", .tags = 1 << 2 },
	{ .title = "Event Tester", .noswallow = 1 },
	{ .class = "spterm", .scratchkey = 't', .isfloating = 1, .floatpos = "50% 50% 85% 85%" },
	{ .class = "spfm", .scratchkey = 'r', .isfloating = 1, .floatpos = "50% 50% 75% 75%" },
};

/* layout(s) */
static const float mfact     		= 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     		= 1;    /* number of clients in master area */
static const int resizehints 		= 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen 	= 1; /* 1 will force focus on the fullscreen window */
static int floatposgrid_x           = 5;        /* float grid columns */
static int floatposgrid_y           = 5;        /* float grid rows */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const char *toggle_float_pos	= "50% 50% 80% 80%"; // default floating position when triggering togglefloating

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static const char *termcmd[]  	= { "st", "-T", "Terminal", NULL };
static const char *webcmd[]		= { "firefox", NULL };
static const char *fmcmd[]		= { "thunar", NULL };
static const char *dmenucmd[]	= { "dmenu_run", "-fn", dmenufont, "-nb", normbgcolor, "-nf", selfloatcolor, "-sb", tagsselbgcolor, "-sf", ltsymbolfgcolor, NULL };
static const char *roficmd[]	= { "rofi", "-show", "drun", NULL };

static const char *blup[]		= { "brightness", "--inc", NULL };
static const char *bldown[]		= { "brightness", "--dec", NULL };

static const char *volup[]		= { "volume", "--inc", NULL };
static const char *voldown[]	= { "volume", "--dec", NULL };
static const char *volmute[]	= { "volume", "--toggle", NULL };
static const char *micmute[]	= { "volume", "--toggle-mic", NULL };

static const char *sptermcmd[] 	= { "t", "st", "-c", "spterm,spterm", NULL }; 
static const char *spfmcmd[] 	= { "r", "st", "-c", "spfm,spfm", "-e", "ranger", NULL }; 

#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_space,  spawn,          {.v = roficmd } },
	{ MODKEY|ControlMask,           XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = webcmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = fmcmd } },
	{ 0, 							XF86XK_AudioMute, 			spawn, {.v = volmute } },
	{ 0, 							XF86XK_AudioMicMute, 		spawn, {.v = micmute } },
	{ 0, 							XF86XK_AudioLowerVolume, 	spawn, {.v = volup } },
	{ 0, 							XF86XK_AudioRaiseVolume, 	spawn, {.v = voldown } },
	{ 0, 							XF86XK_MonBrightnessUp, 	spawn, {.v = blup } },
	{ 0, 							XF86XK_MonBrightnessDown, 	spawn, {.v = bldown } },
	{ MODKEY,						XK_grave,  togglescratch,  {.v = sptermcmd } },
	{ MODKEY,						XK_r,      togglescratch,  {.v = spfmcmd } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_equal,  incrgaps,       {.i = +1 } },
	{ MODKEY,                       XK_minus,  incrgaps,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_g,      togglegaps,     {0} },
	{ MODKEY|ControlMask,    		XK_g,      defaultgaps,    {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} }, 
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_b,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[11]} },
	{ MODKEY,						XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY,           			XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_Right,  viewnext,       {0} },
	{ MODKEY,                       XK_Left,   viewprev,       {0} },
	{ MODKEY|ShiftMask,             XK_Right,  tagtonext,      {0} },
	{ MODKEY|ShiftMask,             XK_Left,   tagtoprev,      {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkButton,		0,		Button1,	spawn,		{.v = dmenucmd } },
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

