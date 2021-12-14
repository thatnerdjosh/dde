/* See LICENSE file for copyright and license details. */
static const char* version 			= "dwm-6.2";

/* appearance options */


/* gaps */
static const bool enablegaps 		= true; 	/* option to turn off gaps completely */
static const unsigned int gappih 	= 10; 		/* horizontal inner gap between windows */
static const unsigned int gappiv 	= 10; 		/* vertical inner gap between windows */
static const unsigned int gappoh 	= 10; 		/* horizontal outer gap between windows and screen edge */
static const unsigned int gappov 	= 10; 		/* vertical outer gap between windows and screen edge */
static const int smartgaps 			= 0; 		/* 1 means no outer gap when there is only one windows */

static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int barheight = 0; 		/* 0 means automatic */
static const unsigned int barbottom = 4; 		/* size of the small rect below the bar to create a 3D effect */
static const int bartextheightoffset = 0;       /* vertical offset for the dwm bar text */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const bool enable3dbar 		= true;

/* fonts */
static const char *fonts[]          = { "mononoki:size=14" };
static const char dmenufont[]       = "mononoki:size=14";

/* colors */
static const char normfgcolor[]     = "#d8dee9";
static const char normbgcolor[]     = "#3b4252";
static const char selfgcolor[]      = "#2e3440";
static const char nomrbordercolor[] = "#2E3440";
static const char selbgcolor[]      = "#a3be8c";
static const char normfgshadowcolor[]     = "#363B48";
static const char selfgshadowcolor[]      = "#91B175";

static const char *colors[][3]      = {
	/*           	    	fg         		bg         		border   */
	[SchemeNorm] 		= { normfgcolor, 	normbgcolor, 	nomrbordercolor },
	[SchemeSel]  		= { selfgcolor, 	selbgcolor, 	selbgcolor  },
	[SchemeStatus]  	= { normfgcolor, 	normbgcolor,  	"#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  	= { selfgcolor, 	selbgcolor,  	"#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsNorm]  	= { normfgcolor, 	normbgcolor,  	"#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
	[SchemeInfoSel]  	= { selfgcolor, 	selbgcolor,  	"#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
	[SchemeInfoNorm]  	= { normfgcolor, 	normbgcolor,  	"#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
	[SchemeNormShadow] 	= { normfgshadowcolor, 	"#000000",  "#000000"  }, // Shadow of selected tag
	[SchemeSelShadow]  	= { selfgshadowcolor, 	"#000000",  	"#000000"  }, // Shadow of selected tag
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
	//{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

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
static const char *dmenucmd[] 		= { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  		= { "alacritty", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },

	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY, 			            XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },

	/* layouts */
	{ MODKEY, 						XK_y, 	   layoutmenu, 	   {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	//{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	/* change focus between monitors */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = -1 } },


	/* gaps */
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY|Mod1Mask,              XK_h,      incrgaps,       {.i = +4 } },
	{ MODKEY|Mod1Mask,              XK_l,      incrgaps,       {.i = -4 } },
	//{ MODKEY|Mod1Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +4 } },
	//{ MODKEY|Mod1Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -4 } },
	//{ MODKEY|Mod1Mask|ControlMask,  XK_h,      incrigaps,      {.i = +4 } },
	//{ MODKEY|Mod1Mask|ControlMask,  XK_l,      incrigaps,      {.i = -4 } },
	//{ MODKEY,                       XK_y,      incrihgaps,     {.i = +4 } },
	//{ MODKEY,                       XK_o,      incrihgaps,     {.i = -4 } },
	//{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +4 } },
	//{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -4 } },
	//{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +4 } },
	//{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -4 } },
	//{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +4 } },
	//{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -4 } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        layoutmenu,     {0} },
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

