#pragma once
#ifndef __PL_QUICKDRAW_H__
#define __PL_QUICKDRAW_H__

#include "PLCore.h"
#include "QDGraf.h"
#include "SharedTypes.h"

struct Dialog;

enum IconAlignmentType
{
	atNone
};

enum IconTransformType
{
	ttNone
};

enum IconSuiteFlags
{
	svAllLargeData = 1,
};

enum TextFlags
{
	bold = 1,
};

enum SystemFontID
{
	systemFont = 0,	// System font
	applFont = 1,	// Application font
};

enum SystemColorID
{
	whiteColor = 1,
	blackColor,
	yellowColor,
	magentaColor,
	redColor,
	cyanColor,
	greenColor,
	blueColor,
};

enum CopyBitsMode
{
	srcCopy,
	srcOr,
	srcXor,
	transparent,
};

enum PenModeID
{
	patOr = transparent + 1,
	patXor,
};

struct CIcon
{
};

struct BitMap
{
	Rect m_rect;
	GpPixelFormat_t m_pixelFormat;
	size_t m_pitch;
	void *m_data;

	void Init(const Rect &rect, GpPixelFormat_t pixelFormat, size_t pitch, void *dataPtr);
};

struct RGBColor
{
	unsigned short red;
	unsigned short green;
	unsigned short blue;
};

typedef GDevice *GDPtr;
typedef GDPtr *GDHandle;

typedef CIcon *CIconPtr;
typedef CIconPtr *CIconHandle;

typedef PortabilityLayer::QDPort GrafPort;
typedef GrafPort *GrafPtr;

typedef Byte Pattern[8];

void GetPort(GrafPtr *graf);
void SetPort(GrafPtr graf);
void SetPortWindowPort(WindowPtr window);
void SetPortDialogPort(Dialog *dialog);

void BeginUpdate(WindowPtr graf);
void EndUpdate(WindowPtr graf);

OSErr GetIconSuite(Handle *suite, short resID, IconSuiteFlags flags);
OSErr PlotIconSuite(Rect *rect, IconAlignmentType alignType, IconTransformType transformType, Handle iconSuite);

CIconHandle GetCIcon(short resID);
OSErr PlotCIcon(Rect *rect, CIconHandle icon);
void DisposeCIcon(CIconHandle icon);

void SetRect(Rect *rect, short left, short top, short right, short bottom);

GDHandle GetMainDevice();

void TextSize(int sz);
void TextFace(int face);
void TextFont(int fontID);
int TextWidth(const PLPasStr &str, int firstChar1Based, int length);
void MoveTo(int x, int y);
void LineTo(int x, int y);
void SetOrigin(int x, int y);
void ForeColor(SystemColorID color);
void BackColor(SystemColorID color);
void GetForeColor(RGBColor *color);
void Index2Color(int index, RGBColor *color);
void RGBForeColor(const RGBColor *color);
void DrawString(const PLPasStr &str);
void PaintRect(const Rect *rect);
void PaintOval(const Rect *rect);
void PaintRgn(RgnHandle region);

void ClipRect(const Rect *rect);	// Sets the clipping area
void FrameRect(const Rect *rect);
void FrameOval(const Rect *rect);
void FrameRoundRect(const Rect *rect, int w, int h);
void PenMode(CopyBitsMode copyBitsMode);
void PenMode(PenModeID mode);
void PenPat(const Pattern *pattern);
void PenSize(int w, int h);
void PenNormal();
void EraseRect(const Rect *rect);
void InvertRect(const Rect *rect);
void InsetRect(Rect *rect, int x, int y);
void Line(int x, int y);	// FIXME: Is this relative or absolute?
Pattern *GetQDGlobalsGray(Pattern *pattern);
Pattern *GetQDGlobalsBlack(Pattern *pattern);

// Finds a pattern from a 'PAT#' resource
// Index is 1-based
void GetIndPattern(Pattern *pattern, int patListID, int index);


void CopyBits(const BitMap *srcBitmap, BitMap *destBitmap, const Rect *srcRect, const Rect *destRect, CopyBitsMode copyMode, RgnHandle maskRegion);
void CopyMask(const BitMap *srcBitmap, const BitMap *maskBitmap, BitMap *destBitmap, const Rect *srcRect, const Rect *maskRect, const Rect *destRect);

RgnHandle NewRgn();
void RectRgn(RgnHandle region, const Rect *rect);
void UnionRgn(RgnHandle regionA, RgnHandle regionB, RgnHandle regionC);
void DisposeRgn(RgnHandle rgn);
void OpenRgn();
void CloseRgn(RgnHandle rgn);
Boolean PtInRgn(Point point, RgnHandle rgn);

void GetClip(RgnHandle rgn);
void SetClip(RgnHandle rgn);

BitMap *GetPortBitMapForCopyBits(CGrafPtr grafPtr);
CGrafPtr GetWindowPort(WindowPtr window);
RgnHandle GetPortVisibleRegion(CGrafPtr port, RgnHandle region);

// Computes A - B and returns it packed?
Int32 DeltaPoint(Point pointA, Point pointB);

// Subtracts srcPoint from destPoint (reverse of DeltaPoint)
void SubPt(Point srcPoint, Point *destPoint);

Boolean SectRect(const Rect *rectA, const Rect *rectB, Rect *outIntersection);

Boolean PtInRect(Point point, const Rect *rect);

void RestoreDeviceClut(void *unknown);
void PaintBehind(void *unknown, RgnHandle region);

RgnHandle GetGrayRgn();	// Returns the region not occupied by the menu bar

#endif