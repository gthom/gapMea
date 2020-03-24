#include "entitycolor.h"

EntityColor::EntityColor()
 : _titleBackground( "#D6FF9A" ), _background( "#FFFFA4" ),
   _text( "#FFFFFF" )
{}

EntityColor::EntityColor( const QColor& titleBackground,
                          const QColor& background,
                          const QColor& text )
 : _titleBackground( titleBackground ), _background( background ),
   _text( text )
{}

QColor EntityColor::titleBackground() const
{
    return _titleBackground;
}

void EntityColor::setTitleBackground( const QColor& titleBackground )
{
    _titleBackground = titleBackground;
}

QColor EntityColor::background() const
{
    return _background;
}

void EntityColor::setBackground( const QColor& background )
{
    _background = background;
}

QColor EntityColor::text() const
{
    return _text;
}

void EntityColor::setText( const QColor& text )
{
    _text = text;
}
