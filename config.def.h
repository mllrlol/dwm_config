/* See LICENSE file for copyright and license details. */
#define TERMINAL "st"
#define BROWSER "librewolf"

/* appearance */
static const unsigned int borderpx	= 1;		/* border pixel of windows */
static const unsigned int snap		= 32;		/* snap pixel */
static const int showbar		= 1;		/* 0 means no bar */
static const int topbar			= 1;		/* 0 means bottom bar */
static const char *fonts[]		= { "JetBrains Mono:size=11" };
static const char dmenufont[]		= "JetBrains Mono:size=11";

static const unsigned int gappx     = 5;        /* gaps between windows */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */

#include </home/bandras/.cache/wal/colors-wal-dwm.h>

/* tagging */
static const char *tags[] = { ">_", "0101", "www", ";)", "|V|" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     		instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    		NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "st-256color",      	NULL,     NULL,           0,         0,          1,           1,        -1 },
	{ "LibreWolf",      	NULL,     NULL,           0,         0,          0,           1,        -1 },
	{ NULL,      		NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = .5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", norm_fg, "-nf", sel_bg, "-sb", sel_fg, "-sf", sel_border, NULL };
static const char *termcmd[]  = { "/usr/local/bin/st", NULL };

static const Key keys[] = {
	/* modifier			key		function	argument */
	{ MODKEY,			XK_space,	spawn,		{.v = dmenucmd } },
	{ MODKEY|ShiftMask,		XK_Return,	spawn,		{.v = termcmd } },
	{ MODKEY,			XK_b,		togglebar,	{0} },
	{ MODKEY,			XK_j,		focusstack,	{.i = +1 } },
	{ MODKEY,			XK_k,		focusstack,	{.i = -1 } },
	{ MODKEY,			XK_i,		incnmaster,	{.i = +1 } },
	{ MODKEY,			XK_d,		incnmaster,	{.i = -1 } },
	{ MODKEY,			XK_h,		setmfact,	{.f = -0.05} },
	{ MODKEY,			XK_l,		setmfact,	{.f = +0.05} },
	{ MODKEY,			XK_Return,	zoom,		{0} },
	{ MODKEY,			XK_q,		killclient,	{0} },
	{ MODKEY,			XK_t,		setlayout,	{.v = &layouts[0]} },
	{ MODKEY,			XK_f,		setlayout,	{.v = &layouts[1]} },
	{ MODKEY,			XK_m,		setlayout,	{.v = &layouts[2]} },
	{ MODKEY,			XK_s,		setlayout,	{0} },
	{ MODKEY|ShiftMask,		XK_space,	togglefloating,	{0} },
	{ MODKEY,			XK_0,		view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,		tag,		{.ui = ~0 } },
	{ MODKEY,			XK_comma,	focusmon,	{.i = -1 } },
	{ MODKEY,			XK_period,	focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_comma,	tagmon,		{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_period,	tagmon,		{.i = +1 } },

	// Browser stuff
	{ MODKEY|ShiftMask,		XK_b,		spawn,		{.v = (const char*[]) { BROWSER, NULL } } },
	{ MODKEY|ShiftMask,             XK_c,		spawn,		{.v = (const char*[]) { BROWSER, "www.discord.com/login", NULL } } },
	{ MODKEY|ShiftMask,             XK_y,		spawn,		{.v = (const char*[]) { BROWSER, "music.youtube.com", NULL } } },
	{ MODKEY|ShiftMask,             XK_p,		spawn,		{.v = (const char*[]) { BROWSER, "www.youtube.com", NULL } } },
	{ MODKEY|ShiftMask,             XK_k,		spawn,		{.v = (const char*[]) { BROWSER, "www.messenger.com", NULL } } },
	{ MODKEY|ShiftMask,             XK_i,		spawn,		{.v = (const char*[]) { BROWSER, "www.instagram.com", NULL } } },

	// Apps
	{ MODKEY|ShiftMask,		XK_e,		spawn,		{.v = (const char*[]) { TERMINAL, "-e", "nvim", NULL } } },
	{ MODKEY|ShiftMask,		XK_w,		spawn,		{.v = (const char*[]) { TERMINAL, "-e", "iwctl", NULL } } },
	{ MODKEY|ShiftMask,		XK_f,		spawn,		{.v = (const char*[]) { TERMINAL, "-e", "lf", NULL } } },
	{ MODKEY|ShiftMask,		XK_g,		spawn,		{.v = (const char*[]) { TERMINAL, "-e", "gimp", NULL } } },

	// Shell stuff
	{ MODKEY|ControlMask,		XK_o,		spawn,		SHCMD("poweroff") },
	{ MODKEY|ControlMask,		XK_i,		spawn,		SHCMD("reboot") },
	{ MODKEY|ControlMask,		XK_l,		spawn,		SHCMD("xrandr --output HDMI3 --auto --left-of eDP1") },
	{ MODKEY|ControlMask,		XK_r,		spawn,		SHCMD("xrandr --output HDMI3 --auto --right-of eDP1") },
	{ MODKEY|ControlMask,		XK_m,		spawn,		SHCMD("xrandr --output HDMI3 --auto --same-as eDP1") },
	{ MODKEY|ControlMask,		XK_n,		spawn,		SHCMD("xrandr --output HDMI3 --off") },

	// Patch stuff
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	
	TAGKEYS(			XK_1,				0)
	TAGKEYS(			XK_2,				1)
	TAGKEYS(			XK_3,				2)
	TAGKEYS(			XK_4,				3)
	TAGKEYS(			XK_5,				4)
	TAGKEYS(			XK_6,				5)
	TAGKEYS(			XK_7,				6)
	TAGKEYS(			XK_8,				7)
	TAGKEYS(                        XK_9,				8)
	{ MODKEY|ShiftMask,		XK_q,		quit,		{0} },
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

