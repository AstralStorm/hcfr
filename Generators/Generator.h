/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2005-2011 Association Homecinema Francophone.  All rights reserved.
/////////////////////////////////////////////////////////////////////////////
//
//  This file is subject to the terms of the GNU General Public License as
//  published by the Free Software Foundation.  A copy of this license is
//  included with this software distribution in the file COPYING.htm. If you
//  do not have a copy, you may obtain a copy by writing to the Free
//  Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
//
//  This software is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details
/////////////////////////////////////////////////////////////////////////////
//  Author(s):
//	Fran?ois-Xavier CHABOUD
/////////////////////////////////////////////////////////////////////////////

// Generator.h: interface for the CGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERATOR_H__A28653EC_9D7F_406C_8F30_9D7187AFFC97__INCLUDED_)
#define AFX_GENERATOR_H__A28653EC_9D7F_406C_8F30_9D7187AFFC97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FullScreenWindow.h"
#include "GeneratorPropPage.h"
#include "../libnum/numsup.h"
#include "../libconv/conv.h"
#include "../libccast/ccmdns.h"
#include "../libccast/ccwin.h"
#include "../libccast/ccast.h"
#include "../Tools/GoogleCastWrapper/GoogleCastWrapper.h"

typedef int (__stdcall *RB8PG_send)(SOCKET sock,const char *message);
typedef int (__stdcall *RB8PG_close)(SOCKET sock);
typedef SOCKET (__stdcall *RB8PG_connect)(const char *server_addr);
typedef char * (__stdcall *RB8PG_discovery)();
typedef char * (__stdcall *RB8PG_get)(SOCKET sock,const char *message);

class CGenerator: public CObject    
{
public:
	DECLARE_SERIAL(CGenerator) ;
	enum MeasureType
	{
		MT_SPECIAL = -2,
		MT_ACTUAL = -1,
		MT_UNKNOWN = 0,
		MT_IRE = 1,
		MT_NEARBLACK,
		MT_NEARWHITE,
		MT_PRIMARY,
		MT_SECONDARY,
		MT_SAT_RED,
		MT_SAT_GREEN,
		MT_SAT_BLUE,
		MT_SAT_YELLOW,
		MT_SAT_CYAN,
		MT_SAT_MAGENTA,
		MT_SAT_CC24_GCD,
		MT_SAT_CC24_MCD,
		MT_SAT_CC24_CMC,
		MT_SAT_CC24_CMS,
		MT_SAT_CC24_CPS,
		MT_SAT_CC24_SKIN,
		MT_SAT_CC24_CCSG,
		MT_SAT_CC24_AXIS,
		MT_SAT_CC24_USER,
		MT_CONTRAST,
		MT_CALIBRATE,
		MT_SAT_ALL
	};

	UINT nMeasureNumber;
	BOOL m_doScreenBlanking;
	UINT m_rectSizePercent;
	int	 m_offsetx,m_offsety;
	BOOL m_b16_235;
	BOOL m_busePic;
	BOOL m_bLinear;
	BOOL m_bHdr10;
	BOOL m_bdispTrip,m_brPi_user;
    BOOL m_madVR_3d;
    BOOL m_madVR_vLUT, m_madVR_HDR;
	BOOL m_madVR_OSD;
	UINT m_ccastIp; 
	SOCKET sock;
	int rPi_xWidth;
	int rPi_yHeight;
	int rPi_memSize;
	dispwin *ccwin;
	RB8PG_send _RB8PG_send;
	RB8PG_close _RB8PG_close;
	RB8PG_connect _RB8PG_connect;
	RB8PG_discovery _RB8PG_discovery;
	RB8PG_get	_RB8PG_get;
	char * pi_Res;

protected:
	HINSTANCE hInstLibrary;
	BOOL m_isModified;
	CFullScreenWindow m_blankingWindow;

	CPropertySheetWithHelp m_propertySheet;
	CGeneratorPropPage m_GeneratorPropertiePage;
	CString m_name;

public:
	CGenerator();
	virtual ~CGenerator();

	virtual	void Copy(CGenerator * p);
	virtual void Serialize(CArchive& archive); 

	virtual BOOL Init(UINT nbMeasure = 0, bool isSpecial =  FALSE);
	virtual BOOL DisplayGray(double aLevel,MeasureType nPatternType, BOOL bChangePattern = TRUE);
	virtual BOOL DisplayRGBColor(const ColorRGBDisplay& aRGBColor, MeasureType nPatternType, UINT nPatternInfo = 0,BOOL bChangePattern = TRUE,BOOL bSilentMode = FALSE);	// need to be overriden
	virtual BOOL DisplayRGBColormadVR(const ColorRGBDisplay& aRGBColor, MeasureType nPatternType = MT_UNKNOWN, UINT nPatternInfo = 0);	// need to be overriden
	virtual BOOL DisplayRGBColorrPI(const ColorRGBDisplay& aRGBColor, MeasureType nPatternType = MT_UNKNOWN, UINT nPatternInfo = 0);	// need to be overriden
	virtual BOOL DisplayRGBCCast(const ColorRGBDisplay& aRGBColor, MeasureType nPatternType = MT_UNKNOWN, UINT nPatternInfo = 0);	// need to be overriden
	virtual BOOL DisplayAnsiBWRects(BOOL bInvert);		// need to be overriden
	virtual BOOL DisplayAnimatedBlack();				// need to be overriden
	virtual BOOL DisplayAnimatedWhite();				// need to be overriden
	virtual BOOL DisplayGradient();				// need to be overriden
	virtual BOOL DisplayGradient2();				// need to be overriden
	virtual BOOL DisplayRG();				// need to be overriden
	virtual BOOL DisplayRB();				// need to be overriden
	virtual BOOL DisplayGB();				// need to be overriden
	virtual BOOL DisplayRGd();				// need to be overriden
	virtual BOOL DisplayRBd();				// need to be overriden
	virtual BOOL DisplayGBd();				// need to be overriden
	virtual BOOL DisplayLramp();				// need to be overriden
	virtual BOOL DisplayGranger();				// need to be overriden
	virtual BOOL Display80();				// need to be overriden
	virtual BOOL DisplaySpectrum();				// need to be overriden
	virtual BOOL DisplaySramp();				// need to be overriden
	virtual BOOL DisplayTestimg();				// need to be overriden
	virtual BOOL DisplayISO12233();				// need to be overriden
	virtual BOOL DisplayNB();				// need to be overriden
	virtual BOOL DisplayNBO();				// need to be overriden
	virtual BOOL DisplayBBCHD();				// need to be overriden
	virtual BOOL DisplayCROSSd();				// need to be overriden
	virtual BOOL DisplayCROSSl();				// need to be overriden
	virtual BOOL DisplayPM5644();				// need to be overriden
	virtual BOOL DisplayZONE();				// need to be overriden
	virtual BOOL DisplayVSMPTE();				// need to be overriden
	virtual BOOL DisplayEramp();				// need to be overriden
	virtual BOOL DisplayAlign();				// need to be overriden
	virtual BOOL DisplayAlign2();				// need to be overriden
	virtual BOOL DisplayUser1();				// need to be overriden
	virtual BOOL DisplayUser2();				// need to be overriden
	virtual BOOL DisplayUser3();				// need to be overriden
	virtual BOOL DisplayUser4();				// need to be overriden
	virtual BOOL DisplayUser5();				// need to be overriden
	virtual BOOL DisplayUser6();				// need to be overriden
	virtual BOOL DisplayTC0();				// need to be overriden
	virtual BOOL DisplayTC1();				// need to be overriden
	virtual BOOL DisplayTC2();				// need to be overriden
	virtual BOOL DisplayTC3();				// need to be overriden
	virtual BOOL DisplayTC4();				// need to be overriden
	virtual BOOL DisplayTC5();				// need to be overriden
	virtual BOOL DisplayBN();				// need to be overriden
	virtual BOOL DisplayDR0();				// need to be overriden
	virtual BOOL DisplayDR1();				// need to be overriden
	virtual BOOL DisplayDR2();				// need to be overriden
	virtual BOOL DisplaySharp();				// need to be overriden
	virtual BOOL DisplayClipL();				// need to be overriden
	virtual BOOL DisplayClipLO();				// need to be overriden
	virtual BOOL DisplayClipH();				// need to be overriden
	virtual BOOL DisplayClipHO();				// need to be overriden
	virtual BOOL DisplayTV();				// need to be overriden
	virtual BOOL DisplayTV2();				// need to be overriden
	virtual BOOL DisplayDotPattern(const ColorRGBDisplay& clr , BOOL dot2, UINT nPads)  { return TRUE; };
	virtual BOOL DisplayHVLinesPattern(const ColorRGBDisplay& clr , BOOL dot2, BOOL vLines)  { return TRUE; };
	virtual BOOL DisplayColorLevelPattern( INT clrLevel , BOOL dot2, UINT nPads) { return TRUE; };
	virtual BOOL DisplayGeomPattern(BOOL dot2, UINT nPads) { return TRUE; };
	virtual BOOL DisplayConvPattern(BOOL dot2, UINT nPads) { return TRUE; };
	virtual BOOL DisplayColorPattern( BOOL dot2) { return TRUE; };
	virtual BOOL DisplayPatternPicture(HMODULE hInst, UINT nIDResource, BOOL bResizePict) { return TRUE; };

	virtual BOOL CanDisplayAnsiBWRects(); 
	virtual BOOL CanDisplayGrayAndColorsSeries()	{ return TRUE; }
	virtual BOOL CanDisplayAnimatedPatterns(BOOL isSpecialty = TRUE)		{ return TRUE; }
	virtual BOOL CanDisplayScale ( MeasureType nScaleType, int nbLevels, BOOL bMute = FALSE )		{ return TRUE; }
	virtual	BOOL HasPatternChanged( MeasureType nScaleType, CColor previousColor,CColor measuredColor)		{ return TRUE; }
	virtual CString GetRetryMessage () { return ""; }
	virtual BOOL Release(INT nbNext = -1);
	virtual BOOL ChangePatternSeries();
	virtual void SetPropertiesSheetValues();
	virtual void GetPropertiesSheetValues();
	virtual BOOL Configure();
	virtual BOOL IsModified() { return m_isModified; }
	virtual void SetModifiedFlag( BOOL bModified ) { m_isModified = bModified; }
	LPVOID ramp; //currently loaded gamma tables

	CString GetName() { return m_name; }
	void SetName(CString aStr) { m_name=aStr; } 

	virtual CString GetActiveDisplayName() { return ""; }

protected:
	void AddPropertyPage(CPropertyPageWithHelp *apPage);
};

#endif // !defined(AFX_GENERATOR_H__A28653EC_9D7F_406C_8F30_9D7187AFFC97__INCLUDED_)
