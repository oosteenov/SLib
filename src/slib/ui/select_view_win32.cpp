#include "../../../inc/slib/core/definition.h"

#if defined(SLIB_PLATFORM_IS_WIN32)

#include "../../../inc/slib/ui/select_view.h"

#include "view_win32.h"

SLIB_UI_NAMESPACE_BEGIN

class _SelectView : public SelectView
{
public:
	void __applyItemsCount(HWND hWnd)
	{
		ObjectLocker lock(this);
		sl_uint32 nOrig = (sl_uint32)(::SendMessageW(hWnd, CB_GETCOUNT, 0, 0));
		sl_uint32 nNew = (sl_uint32)(m_titles.getCount());
		if (nOrig == nNew) {
			return;
		}
		if (nOrig > nNew) {
			if (nNew > 0) {
				for (sl_uint32 i = nOrig; i > nNew; i--) {
					::SendMessageW(hWnd, CB_DELETESTRING, (WPARAM)(i - 1), 0);
				}
			} else {
				::SendMessageW(hWnd, CB_RESETCONTENT, 0, 0);
			}
		} else {
			for (sl_uint32 i = nOrig; i < nNew; i++) {
				String16 s = m_titles.getValueAt(i);
				::SendMessageW(hWnd, CB_ADDSTRING, 0, (LPARAM)(s.getData()));
			}
		}
	}

	void __copyItems(HWND hWnd)
	{
		::SendMessageW(hWnd, CB_RESETCONTENT, 0, 0);
		__applyItemsCount(hWnd);
		sl_uint32 n = (sl_uint32)(m_titles.getCount());
		if (m_indexSelected >= n) {
			m_indexSelected = 0;
		}
		if (n > 0) {
			::SendMessageW(hWnd, CB_SETCURSEL, (WPARAM)m_indexSelected, 0);
		}
	}

	void __setItemTitle(HWND hWnd, sl_uint32 index, const String& title)
	{
		String16 s = title;
		::SendMessageW(hWnd, CB_DELETESTRING, (WPARAM)index, 0);
		::SendMessageW(hWnd, CB_INSERTSTRING, (WPARAM)index, (LPARAM)(s.getData()));
	}

	sl_uint32 __getSelectedIndex(HWND hWnd)
	{
		return (sl_uint32)(::SendMessageW(hWnd, CB_GETCURSEL, 0, 0));
	}

	void __onSelectItem(HWND hWnd)
	{
		dispatchSelectItem(__getSelectedIndex(hWnd));
	}

};

class _Win32_SelectViewInstance : public Win32_ViewInstance
{
public:
    // override
	sl_bool processWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam, LRESULT& result)
	{
		return sl_false;
	}

    // override
	sl_bool processCommand(SHORT code, LRESULT& result)
	{
		if (code == CBN_SELCHANGE) {
			Ref<View> view = getView();
			if (_SelectView* _view = CastInstance<_SelectView>(view.get())) {
				_view->__onSelectItem(m_handle);
			}
			return sl_true;
		}
		return sl_false;
	}
};

Ref<ViewInstance> SelectView::createNativeWidget(ViewInstance* parent)
{
	Win32_UI_Shared* shared = Win32_UI_Shared::get();
	if (!shared) {
		return sl_null;
	}

	UINT style = CBS_DROPDOWNLIST | WS_TABSTOP;
	Ref<_Win32_SelectViewInstance> ret = Win32_ViewInstance::create<_Win32_SelectViewInstance>(this, parent, L"COMBOBOX", L"", style, 0);
	
	if (ret.isNotNull()) {

		HWND handle = ret->getHandle();

		Ref<Font> font = getFont();
		HFONT hFont = GraphicsPlatform::getGdiFont(font.get());
		if (hFont) {
			::SendMessageW(handle, WM_SETFONT, (WPARAM)hFont, TRUE);
		}

		((_SelectView*)this)->__copyItems(handle);
	}
	return ret;
}

void SelectView::_getSelectedIndex_NW()
{
	HWND handle = UIPlatform::getViewHandle(this);
	if (handle) {
		m_indexSelected = ((_SelectView*)this)->__getSelectedIndex(handle);
	}
}

void SelectView::_select_NW(sl_uint32 index)
{
	HWND handle = UIPlatform::getViewHandle(this);
	if (handle) {
		::SendMessageW(handle, CB_SETCURSEL, (WPARAM)index, 0);
	}
}

void SelectView::_refreshItemsCount_NW()
{
	HWND handle = UIPlatform::getViewHandle(this);
	if (handle) {
		((_SelectView*)this)->__applyItemsCount(handle);
	}
}

void SelectView::_refreshItemsContent_NW()
{
	HWND handle = UIPlatform::getViewHandle(this);
	if (handle) {
		((_SelectView*)this)->__copyItems(handle);
	}
}

void SelectView::_setItemTitle_NW(sl_uint32 index, const String& title)
{
	HWND handle = UIPlatform::getViewHandle(this);
	if (handle) {
		((_SelectView*)this)->__setItemTitle(handle, index, title);
	}
}

void SelectView::_setFont_NW(const Ref<Font>& font)
{
	HWND handle = UIPlatform::getViewHandle(this);
	if (handle) {
		HFONT hFont = GraphicsPlatform::getGdiFont(font.get());
		if (hFont) {
			::SendMessageW(handle, WM_SETFONT, (WPARAM)hFont, TRUE);
		}
	}
}

SLIB_UI_NAMESPACE_END

#endif
