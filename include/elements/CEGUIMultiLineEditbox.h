/************************************************************************
	filename: 	CEGUIMultiLineEditbox.h
	created:	30/6/2004
	author:		Paul D Turner
	
	purpose:	Interface to the Multi-lien edit box base class.
*************************************************************************/
/*************************************************************************
    Crazy Eddie's GUI System (http://crayzedsgui.sourceforge.net)
    Copyright (C)2004 Paul D Turner (crayzed@users.sourceforge.net)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*************************************************************************/
#ifndef _CEGUIMultiLineEditbox_h_
#define _CEGUIMultiLineEditbox_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "CEGUIFont.h"
#include "elements/CEGUIMultiLineEditboxProperties.h"

#include <vector>


// Start of CEGUI namespace section
namespace CEGUI
{
/*!
\brief
	Base class for the multi-line edit box widget.
*/
class CEGUIBASE_API MultiLineEditbox : public Window
{
public:
	/*************************************************************************
		Constants
	*************************************************************************/
	// event names
	static const utf8	ReadOnlyChanged[];					//!< The read-only mode for the edit box has been changed.
	static const utf8	WordWrapModeChanged[];				//!< The word wrap mode of the text box has been changed.
	static const utf8	MaximumTextLengthChanged[];			//!< The maximum allowable string length has been changed.
	static const utf8	CaratMoved[];						//!< The text carat (insert point) has changed.
	static const utf8	TextSelectionChanged[];				//!< The current text selection has changed.
	static const utf8	EditboxFullEvent[];					//!< The number of characters in the edit box has reached the current maximum.
	static const utf8	VertScrollbarModeChanged[];			//!< Event triggered when the vertical scroll bar 'force' setting changes.
	static const utf8	HorzScrollbarModeChanged[];			//!< Event triggered when the horizontal scroll bar 'force' setting changes.

	// default colours
	static const ulong	DefaultNormalTextColour;			//!< Colour applied to normal unselected text.
	static const ulong	DefaultSelectedTextColour;			//!< Colour applied to selected text.
	static const ulong	DefaultNormalSelectionColour;		//!< Colour applied to normal selection brush.
	static const ulong	DefaultInactiveSelectionColour;		//!< Colour applied to selection brush when widget is inactive.


	/*************************************************************************
		Accessor Functions
	*************************************************************************/
	/*!
	\brief
		return true if the edit box has input focus.

	\return
		- true if the edit box has keyboard input focus.
		- false if the edit box does not have keyboard input focus.
	*/
	bool	hasInputFocus(void) const;


	/*!
	\brief
		return true if the edit box is read-only.

	\return
		- true if the edit box is read only and can't be edited by the user.
		- false if the edit box is not read only and may be edited by the user.
	*/
	bool	isReadOnly(void) const		{return d_readOnly;}


	/*!
	\brief
		return the current position of the carat.

	\return
		Index of the insert carat relative to the start of the text.
	*/
	ulong	getCaratIndex(void) const		{return d_caratPos;}


	/*!
	\brief
		return the current selection start point.

	\return
		Index of the selection start point relative to the start of the text.  If no selection is defined this function returns
		the position of the carat.
	*/
	ulong	getSelectionStartIndex(void) const;


	/*!
	\brief
		return the current selection end point.

	\return
		Index of the selection end point relative to the start of the text.  If no selection is defined this function returns
		the position of the carat.
	*/
	ulong	getSelectionEndIndex(void) const;

	
	/*!
	\brief
		return the length of the current selection (in code points / characters).

	\return
		Number of code points (or characters) contained within the currently defined selection.
	*/
	ulong	getSelectionLength(void) const;


	/*!
	\brief
		return the maximum text length set for this edit box.

	\return
		The maximum number of code points (characters) that can be entered into this edit box.
	*/
	ulong	getMaxTextLength(void) const		{return d_maxTextLen;}


	/*!
	\brief
		return the currently set colour to be used for rendering edit box text in the
		normal, unselected state.

	\return
		colour value describing the ARGB colour that is currently set.
	*/
	colour	getNormalTextColour(void) const				{return d_normalTextColour;}


	/*!
	\brief
		return the currently set colour to be used for rendering the edit box text when within the
		selected region.

	\return
		colour value describing the ARGB colour that is currently set.
	*/
	colour	getSelectedTextColour(void) const			{return d_selectTextColour;}


	/*!
	\brief
		return the currently set colour to be used for rendering the edit box selection highlight
		when the edit box is active.

	\return
		colour value describing the ARGB colour that is currently set.
	*/
	colour	getNormalSelectBrushColour(void) const		{return d_selectBrushColour;}


	/*!
	\brief
		return the currently set colour to be used for rendering the edit box selection highlight
		when the edit box is inactive.

	\return
		colour value describing the ARGB colour that is currently set.
	*/
	colour	getInactiveSelectBrushColour(void) const	{return d_inactiveSelectBrushColour;}


	/*!
	\brief
		Return whether the text in the edit box will be word-wrapped.

	\return
		- true if the text will be word-wrapped at the edges of the widget frame.
		- false if text will not be word-wrapped (a scroll bar will be used to access long text lines).
	*/
	bool	isWordWrapped(void) const;


	/*************************************************************************
		Manipulators
	*************************************************************************/
	/*!
	\brief
		Initialise the Window based object ready for use.

	\note
		This must be called for every window created.  Normally this is handled automatically by the WindowFactory for each Window type.

	\return
		Nothing
	*/
	virtual void	initialise(void);


	/*!
	\brief
		Specify whether the edit box is read-only.

	\param setting
		- true if the edit box is read only and can't be edited by the user.
		- false if the edit box is not read only and may be edited by the user.

	\return
		Nothing.
	*/
	void	setReadOnly(bool setting);


	/*!
	\brief
		Set the current position of the carat.

	\param carat_pos
		New index for the insert carat relative to the start of the text.  If the value specified is greater than the
		number of characters in the edit box, the carat is positioned at the end of the text.

	\return
		Nothing.
	*/
	void	setCaratIndex(ulong carat_pos);


	/*!
	\brief
		Define the current selection for the edit box

	\param start_pos
		Index of the starting point for the selection.  If this value is greater than the number of characters in the edit box, the
		selection start will be set to the end of the text.

	\param end_pos
		Index of the ending point for the selection.  If this value is greater than the number of characters in the edit box, the
		selection start will be set to the end of the text.

	\return
		Nothing.
	*/
	void	setSelection(ulong start_pos, ulong end_pos);
	

	/*!
	\brief
		set the maximum text length for this edit box.

	\param max_len
		The maximum number of code points (characters) that can be entered into this Editbox.

	\return
		Nothing.
	*/
	void	setMaxTextLength(ulong max_len);


	/*!
	\brief
		Set the colour to be used for rendering edit box text in the normal, unselected state.

	\param col
		colour value describing the ARGB colour that is to be used.

	\return
		Nothing.
	*/
	void	setNormalTextColour(colour col);


	/*!
	\brief
		Set the colour to be used for rendering the edit box text when within the
		selected region.

	\return
		colour value describing the ARGB colour that is currently set.
	*/
	void	setSelectedTextColour(colour col);


	/*!
	\brief
		Set the colour to be used for rendering the edit box selection highlight
		when the edit box is active.

	\param col
		colour value describing the ARGB colour that is to be used.

	\return
		Nothing.
	*/
	void	setNormalSelectBrushColour(colour col);


	/*!
	\brief
		Set the colour to be used for rendering the edit box selection highlight
		when the edit box is inactive.

	\param col
		colour value describing the ARGB colour that is to be used.

	\return
		Nothing.
	*/
	void	setInactiveSelectBrushColour(colour col);


	/*!
	\brief
		Scroll the view so that the current carat position is visible.
	*/
	void	ensureCaratIsVisible(void);


	/*!
	\brief
		Set whether the text will be word wrapped or not.

	\param setting
		- true if the text should word-wrap at the edges of the text box.
		- false if the text should not wrap, but a scroll bar should be used.

	\return
		Nothing.
	*/
	void	setWordWrapping(bool setting);


	/*************************************************************************
		Construction and Destruction
	*************************************************************************/
	/*!
	\brief
		Constructor for the MultiLineEditbox base class.
	*/
	MultiLineEditbox(const String& type, const String& name);


	/*!
	\brief
		Destructor for the MultiLineEditbox base class.
	*/
	virtual ~MultiLineEditbox(void);


protected:
	/*************************************************************************
		Implementation Methods (abstract)
	*************************************************************************/
	/*!
	\brief
		Return a Rect object describing, in un-clipped pixels, the window relative area
		that the text should be rendered in to.

	\return
		Rect object describing the area of the Window to be used for rendering text.
	*/
	virtual	Rect	getTextRenderArea(void) const		= 0;


	/*!
	\brief
		create and return a pointer to a Scrollbar widget for use as vertical scroll bar

	\return
		Pointer to a Scrollbar to be used for scrolling vertically.
	*/
	virtual Scrollbar*	createVertScrollbar(void) const		= 0;
 

	/*!
	\brief
		create and return a pointer to a Scrollbar widget for use as horizontal scroll bar

	\return
		Pointer to a Scrollbar to be used for scrolling horizontally.
	*/
	virtual Scrollbar*	createHorzScrollbar(void) const		= 0;


	/*!
	\brief
		Setup size and position for the component widgets attached to this Editbox

	\return
		Nothing.
	*/
	virtual void	layoutComponentWidgets()	= 0;


	/*!
	\brief
		Perform rendering of the widget control frame and other 'static' areas.  This
		method should not render the actual text.  Note that the text will be rendered
		to layer 4 and the selection brush to layer 3, other layers can be used for
		rendering imagery behind and infront of the text & selection..

	\param z
		Z co-ordinate for layer 0.

	\return
		Nothing.
	*/
	virtual	void	renderEditboxBaseImagery(float z)		= 0;


	/*!
	\brief
		Render the carat.

	\return
		Nothing
	*/
	virtual void	renderCarat(float baseX, float baseY, const Rect& clipper)	= 0;


	/*************************************************************************
		Implementation Methods
	*************************************************************************/
	/*!
	\brief
		Add multi-line edit box specific events
	*/
	void	addMultiLineEditboxEvents(void);


	/*!
	\brief
		Render text lines.
	*/
	void	renderTextLines(const Rect& dest_area, const Rect& clipper) const;


	/*!
	\brief
		Format the text into lines as needed by the current formatting options.
	*/
	void	formatText(void);


	/*!
	\brief
		Return the length of the next token in String \a text starting at index \a start_idx.

	\note
		Any single whitespace character is one token, any group of other characters is a token.
	
	\return
		The code point length of the token.
	*/
	uint	getNextTokenLength(const String& text, uint start_idx) const;


	/*!
	\brief
		Perform the actual rendering for this Window.

	\param z
		float value specifying the base Z co-ordinate that should be used when rendering

	\return
		Nothing
	*/
	virtual	void	drawSelf(float z);


	/*!
	\brief
		display required integrated scroll bars according to current state of the edit box and update their values.
	*/
	void	configureScrollbars(void);


	/*!
	\brief
		Return the text code point index that is rendered closest to screen position \a pt.

	\param pt
		Point object describing a position on the screen in pixels.

	\return
		Code point index into the text that is rendered closest to screen position \pt.
	*/
	uint	getTextIndexFromPosition(const Point& pt) const;


	/*!
	\brief
		Return the line number a given index falls on with the current formatting.  Will return last line
		if index is out of range.
	*/
	uint	getLineNumberFromIndex(uint index) const;


	/*!
	\brief
		Clear the current selection setting
	*/
	void	clearSelection(void);


	/*!
	\brief
		Erase the currently selected text.

	\param modify_text
		when true, the actual text will be modified.  When false, everything is done except erasing the characters.
	*/
	void	eraseSelectedText(bool modify_text = true);


	/*!
	\brief
		Processing for backspace key
	*/
	void	handleBackspace(void);


	/*!
	\brief
		Processing for Delete key
	*/
	void	handleDelete(void);


	/*!
	\brief
		Processing to move carat one character left
	*/
	void	handleCharLeft(uint sysKeys);


	/*!
	\brief
		Processing to move carat one word left
	*/
	void	handleWordLeft(uint sysKeys);


	/*!
	\brief
		Processing to move carat one character right
	*/
	void	handleCharRight(uint sysKeys);


	/*!
	\brief
		Processing to move carat one word right
	*/
	void	handleWordRight(uint sysKeys);


	/*!
	\brief
		Processing to move carat to the start of the text.
	*/
	void	handleDocHome(uint sysKeys);


	/*!
	\brief
		Processing to move carat to the end of the text
	*/
	void	handleDocEnd(uint sysKeys);


	/*!
	\brief
		Processing to move carat to the start of the current line.
	*/
	void	handleLineHome(uint sysKeys);


	/*!
	\brief
		Processing to move carat to the end of the current line
	*/
	void	handleLineEnd(uint sysKeys);


	/*!
	\brief
		Processing to move carat up a line.
	*/
	void	handleLineUp(uint sysKeys);


	/*!
	\brief
		Processing to move carat down a line.
	*/
	void	handleLineDown(uint sysKeys);


	/*!
	\brief
		Processing to insert a new line / paragraph.
	*/
	void	handleNewLine(uint sysKeys);


	/*************************************************************************
		New event handlers
	*************************************************************************/
	/*!
	\brief
		Handler called when the read-only state of the edit box changes
	*/
	void	onReadOnlyChanged(WindowEventArgs& e);


	/*!
	\brief
		Handler called when the word wrap mode for the the edit box changes
	*/
	void	onWordWrapModeChanged(WindowEventArgs& e);


	/*!
	\brief
		Handler called when the maximum text length for the edit box changes
	*/
	void	onMaximumTextLengthChanged(WindowEventArgs& e);


	/*!
	\brief
		Handler called when the carat moves.
	*/
	void	onCaratMoved(WindowEventArgs& e);


	/*!
	\brief
		Handler called when the text selection changes
	*/
	void	onTextSelectionChanged(WindowEventArgs& e);


	/*!
	\brief
		Handler called when the edit box is full
	*/
	void	onEditboxFullEvent(WindowEventArgs& e);


	/*!
	\brief
		Handler called when the 'always show' setting for the vertical scroll bar changes.
	*/
	void	onVertScrollbarModeChanged(WindowEventArgs& e);


	/*!
	\brief
		Handler called when 'always show' setting for the horizontal scroll bar changes.
	*/
	void	onHorzScrollbarModeChanged(WindowEventArgs& e);


	/*************************************************************************
		Overridden event handlers
	*************************************************************************/
	virtual	void	onMouseButtonDown(MouseEventArgs& e);
	virtual void	onMouseButtonUp(MouseEventArgs& e);
	virtual	void	onMouseDoubleClicked(MouseEventArgs& e);
	virtual	void	onMouseTripleClicked(MouseEventArgs& e);
	virtual void	onMouseMove(MouseEventArgs& e);
	virtual void	onCaptureLost(WindowEventArgs& e);
	virtual void	onCharacter(KeyEventArgs& e);
	virtual void	onKeyDown(KeyEventArgs& e);
	virtual void	onTextChanged(WindowEventArgs& e);
	virtual void	onSized(WindowEventArgs& e);


	/*************************************************************************
		Implementation struct
	*************************************************************************/
	/*!
	\brief
		struct used to store information about a formatted line within the
		paragraph.
	*/
	struct LineInfo
	{
		ulong	d_startIdx;		//!< Starting index for this line.
		ulong	d_length;		//!< Code point length of this line.
		float	d_extent;		//!< Rendered extent of this line.
	};


	/*************************************************************************
		Implementation data
	*************************************************************************/
	bool	d_readOnly;			//!< true if the edit box is in read-only mode
	ulong	d_maxTextLen;		//!< Maximum number of characters for this Editbox.
	ulong	d_caratPos;			//!< Position of the carat / insert-point.
	ulong	d_selectionStart;	//!< Start of selection area.
	ulong	d_selectionEnd;		//!< End of selection area.
	bool	d_dragging;			//!< true when a selection is being dragged.
	ulong	d_dragAnchorIdx;	//!< Selection index for drag selection anchor point.

	typedef	std::vector<LineInfo>	LineList;	//!< Type for collection of LineInfos.
	static String d_lineBreakChars;	//!< Holds what we consider to be line break characters.
	bool		d_wordWrap;			//!< true when formatting uses word-wrapping.
	LineList	d_lines;			//!< Holds the lines for the current formatting.
	float		d_widestExtent;		//!< Holds the extent of the widest line as calculated in the last formatting pass.

	// component widgets
	Scrollbar*	d_vertScrollbar;	//!< Points to the vertical scroll bar widget.
	Scrollbar*	d_horzScrollbar;	//!< Points to the horizontal scroll bar widget.
	bool	d_forceVertScroll;		//!< true if vertical scrollbar should always be displayed
	bool	d_forceHorzScroll;		//!< true if horizontal scrollbar should always be displayed

	// images
	const Image*	d_selectionBrush;	//!< Image to use as the selection brush (should be set by derived class).

	// basic rendering colours
	colour	d_normalTextColour;				//!< Text colour used normally.
	colour	d_selectTextColour;				//!< Text colour used when text is highlighted
	colour	d_selectBrushColour;			//!< Colour to apply to the selection brush.
	colour	d_inactiveSelectBrushColour;	//!< Colour to apply to the selection brush when widget is inactive / read-only.


private:
	/*************************************************************************
		Static Properties for this class
	*************************************************************************/
	static MultiLineEditboxProperties::ReadOnly					d_readOnlyProperty;
	static MultiLineEditboxProperties::WordWrap					d_wordWrapProperty;
	static MultiLineEditboxProperties::CaratIndex				d_caratIndexProperty;
	static MultiLineEditboxProperties::SelectionStart			d_selectionStartProperty;
	static MultiLineEditboxProperties::SelectionLength			d_selectionLengthProperty;
	static MultiLineEditboxProperties::MaxTextLength			d_maxTextLengthProperty;
	static MultiLineEditboxProperties::NormalTextColour			d_normalTextColourProperty;
	static MultiLineEditboxProperties::SelectedTextColour		d_selectedTextColourProperty;
	static MultiLineEditboxProperties::ActiveSelectionColour	d_activeSelectionColourProperty;
	static MultiLineEditboxProperties::InactiveSelectionColour	d_inactiveSelectionColourProperty;


	/*************************************************************************
		Private methods
	*************************************************************************/
	void	addMultiLineEditboxProperties(void);
};

} // End of  CEGUI namespace section


#endif	// end of guard _CEGUIMultiLineEditbox_h_
