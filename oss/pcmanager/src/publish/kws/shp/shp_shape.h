////////////////////////////////////////////////////////////////////////////////
//      
//      Kingsoft File for shp routines file
//      
//      File      : shp_shape.h
//      Comment   : simple html parser shape obj class
//					
//      Create at : 2009-02-12
//      Create by : chenguicheng
//      
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "shpsupport.h"

#define SHP_SHAPE_ITEM_KEY				TEXT("shape")
#define SHP_SHAPE_TYPE_KEY				TEXT("shape_type")
#define SHP_SHAPE_BORDER_WIDTH_KEY		TEXT("border_width")
#define SHP_SHAPE_BORDER_COLOR_KEY		TEXT("border_clr")
#define SHP_SHAPE_BORDER_TYPE_KEY		TEXT("border_type")
#define SHP_SHAPE_FILL_KEY				TEXT("fill")
#define SHP_SHAPE_ISBTN_KEY				TEXT("is_btn")


class shp_shape_item : public shp_dom_item
{
public:

	shp_shape_item()
	:m_i_type(INT_NO_SET),
	m_i_border_width(INT_NO_SET),
	m_i_border_style(INT_NO_SET),
	m_clr_border(INT_NO_SET),
	m_i_fill(1),
	m_i_btn(0),
	m_b_over(false),
	m_h_cursor(NULL),
	m_b_hit(true)
	{
		m_h_cursor = ::LoadCursor( NULL, IDC_HAND );
	};

	~shp_shape_item()
	{
	
	};

	//set_attribute( p, m )
	BEGIN_KEY_MAP()
		//to add new attribute map( key map to member )
		ADD_INT_KEY( SHP_SHAPE_TYPE_KEY, m_i_type)
		ADD_INT_KEY( SHP_SHAPE_BORDER_WIDTH_KEY, m_i_border_width)
		ADD_INT_KEY( SHP_SHAPE_BORDER_TYPE_KEY, m_i_border_style)
		ADD_INT_KEY( SHP_SHAPE_FILL_KEY, m_i_fill)
		ADD_INT_KEY( SHP_SHAPE_ISBTN_KEY, m_i_btn)
		ADD_CLR_KEY(SHP_SHAPE_BORDER_COLOR_KEY, m_clr_border)

		BASE_CLASS_PROCESS(shp_item_win32)
	END_KEY_MAP()

	void draw_item( HDC hdc, CRect* parent_rect, CRect *left_rect )
	{
		if ( !m_b_init)
		{
			_init_rect( hdc, parent_rect, left_rect );
			m_b_init = true;
		}

		if ( get_visible())
		{
			_draw_shape( hdc );
		}
	}

	CRect* get_draw_rect()
	{
		return &m_draw_rect;
	}

	virtual LPCTSTR hit_test(  HDC hdc, UINT umsg, int x, int y )
	{
		if( m_i_btn == 0 )
			return NO_PROCESS;

		LPCTSTR lp_str = NULL;

		if ( !get_visible())
		{
			return NULL;
		}
		
		if ( get_state() == SHP_ITEM_STATE_DISABLE )
		{
			return NULL;
		}

		if ( umsg == WM_MOUSELEAVE )
		{
			m_b_over = false;
			m_b_hit = false;
		}

		if ( umsg == WM_MOUSEMOVE)
		{
			lp_str = _mouse_move( hdc, x, y );
		}

		if ( umsg == WM_LBUTTONUP )
		{
			lp_str = _mouse_up( hdc, x, y );
		}

		if ( umsg == WM_LBUTTONDOWN )
		{
			lp_str = _mouse_down( hdc, x, y );
		}

		if ( umsg == WM_NCHITTEST )
		{
			lp_str = _nchittest( hdc, x, y);
		}

		return lp_str;

	}

	LPCTSTR _mouse_move( HDC hdc, int x, int y )
	{
		LPCTSTR lp_str = NULL;
		if ( m_draw_rect.PtInRect( CPoint(x,y)) )
		{
			SetCursor( m_h_cursor );
			m_b_over = true;
			lp_str = m_str_id;
		}
		else
		{
			m_b_over = false;	
		}

		return lp_str;
	}

	LPCTSTR _mouse_down( HDC hdc, int x, int y )
	{
		LPCTSTR lp_str = NULL;
		if ( m_draw_rect.PtInRect(CPoint(x,y)) )
		{
			SetCursor( m_h_cursor );
			lp_str = m_str_id;
			m_b_hit = true;
		}

		return lp_str;
	}

	LPCTSTR _mouse_up( HDC hdc, int x, int y )
	{
		LPCTSTR lp_str = NULL;
		if ( m_draw_rect.PtInRect(CPoint(x,y)) )
		{
			SetCursor( m_h_cursor );
			if ( m_b_hit)
				lp_str = m_str_id;

			m_b_hit = false;
		}
		else
		{
			m_b_hit = false;
		}

		return lp_str;
	}

	LPCTSTR _nchittest( HDC hdc, int x, int y )
	{
		LPCTSTR lp_str = NULL;
		if ( m_draw_rect.PtInRect(CPoint(x,y)) )
		{
			lp_str = m_str_id;
		}

		return lp_str;
	}

	void set_fill(int i_fill)
	{
		m_i_fill = i_fill;
	}

	int get_fill( )
	{
		return m_i_fill;
	}

protected:

	void _draw_shape( HDC hdc)
	{
		ASSERT( m_clr_bg != INT_NO_SET );
		ASSERT( m_i_type != INT_NO_SET );

		if ( m_i_type == 1)
		{
			_draw_rectangle( hdc );
		}

		return;
	}

	void _draw_rectangle( HDC hdc )
	{
		if ( m_i_fill == 1 )
		{
			CBrush brush( ::CreateSolidBrush(m_clr_bg) );
			::FillRect( hdc, m_draw_rect, brush );
		}


		if ( m_i_border_width != INT_NO_SET )
			_draw_border( hdc );
	}

	void _draw_border( HDC hdc )
	{
		CPen pen;
		int pen_type;

		switch( m_i_border_style )
		{
		case INT_NO_SET:
		case 1:
			pen_type = PS_SOLID;
			break;
		case 2:
			pen_type = PS_DOT;
			break;
		case 3:
			pen_type = PS_DASH;
			break;
		}

		if ( m_clr_border == INT_NO_SET )
		{
			m_clr_border = m_clr_bg;
		}

		pen.CreatePen( pen_type, m_i_border_width, m_clr_border );

		HPEN hOldPen = (HPEN)::SelectObject( hdc, HPEN(pen) );

		::MoveToEx( hdc, m_draw_rect.left,		m_draw_rect.top , NULL );
		::LineTo( hdc, m_draw_rect.right,		m_draw_rect.top );
		::LineTo( hdc, m_draw_rect.right,		m_draw_rect.bottom );
		::MoveToEx( hdc, m_draw_rect.right,		m_draw_rect.bottom , NULL );
		::LineTo( hdc, m_draw_rect.left,		m_draw_rect.bottom );
		::LineTo( hdc, m_draw_rect.left,		m_draw_rect.top );
		
		//CBrush brush( ::CreateSolidBrush(m_clr_border));
		//::FrameRect( hdc, &m_draw_rect, brush );
		if ( hOldPen )
			::SelectObject( hdc, hOldPen );
	}
	
	void _init_rect( HDC hdc, CRect *p_rect, CRect *left_rect )
	{
		if ( left_rect )
		{
			m_draw_rect.left	= left_rect->right + m_i_left;
			m_draw_rect.right	= m_draw_rect.left + m_i_width;

			m_draw_rect.top		= p_rect->top + m_i_top;
			m_draw_rect.bottom	= m_draw_rect.top + m_i_height;
		}
		else
		{
			m_draw_rect.left	= p_rect->left + m_i_left;
			m_draw_rect.right	= m_draw_rect.left + m_i_width;

			m_draw_rect.top		= p_rect->top + m_i_top;
			m_draw_rect.bottom	= m_draw_rect.top + m_i_height;
		}
	}

private:

	int			m_i_type;
	int			m_i_border_width;
	int			m_i_border_style;
	shpclr		m_clr_border;

	int			m_i_fill;
	int			m_i_btn;
	bool		m_b_over;
	HCURSOR		m_h_cursor;
	bool		m_b_hit;

};

