#include "config.h"

#define GET_ENTITYCOLOR_VALUE( val )                                     \
    settings.value( "entityColor/" #val ).value< QColor >()

#define SET_ENTITYCOLOR_VALUE( val )                                     \
    settings.setValue( "entityColor/" #val, _entityColor.val().name() )

#define GET_VALUE_COLOR( val )                                           \
    _##val = settings.value( "generalColor/" #val ).value< QColor >()
#define SET_VALUE_COLOR( field )                                         \
    settings.setValue( "generalColor/" #field, _##field.name() )

Config *g_pConfig = Config::singleton(), *config = Config::singleton();

Config* Config::singleton()
{
    // Set core applications stuffs for config file.
    QCoreApplication::setOrganizationName( "gapMea" );
    QCoreApplication::setOrganizationDomain( "github.com/gthom/" );
    QCoreApplication::setApplicationName( "gapMea" );
    QCoreApplication::setApplicationVersion( "1.0" );

    // Default file name configuration.
    static Config _config( "gapMea.conf" );

    return &_config;
}

Config::Config( const QString& fileName )
    : _entityColor(), _fileName( fileName )
{
    refresh();
}

void Config::refresh()
{
    QSettings settings( _fileName, QSettings::Format::IniFormat );

    // Load configuration if it exists, for the moment there is 10 values.
    if ( settings.allKeys().size() )
    {
        getValues();
    }
    else // Otherwhise write default configuration
    {
        setValues();
    }
}

void Config::save()
{
    setValues();
}

void Config::getValues()
{
    QSettings settings( _fileName, QSettings::Format::IniFormat );

    // Entity color values
    _entityColor.setTitleBackground(
      GET_ENTITYCOLOR_VALUE( titleBackground ) );
    _entityColor.setBackground( GET_ENTITYCOLOR_VALUE( background ) );
    _entityColor.setText( GET_ENTITYCOLOR_VALUE( text ) );

    // General color values
    GET_VALUE_COLOR( linkTextColor );
    GET_VALUE_COLOR( linkBackgroundColor );
    GET_VALUE_COLOR( reflectiveLinkBackgroundColor );
    GET_VALUE_COLOR( reflectiveLinkTextColor );
    GET_VALUE_COLOR( assocGradientColor1 );
    GET_VALUE_COLOR( assocGradientColor2 );
    GET_VALUE_COLOR( arrowColor );
    GET_VALUE_COLOR( cardinal1Color );
    GET_VALUE_COLOR( cardinal2Color );
    GET_VALUE_COLOR( roleColor );
    GET_VALUE_COLOR( lineColor );
    GET_VALUE_COLOR( paletteBackgroundColor );
    GET_VALUE_COLOR( paletteTextColor );
}

void Config::setValues()
{
    QSettings settings( _fileName, QSettings::Format::IniFormat );

    // Entity values
    SET_ENTITYCOLOR_VALUE( titleBackground );
    SET_ENTITYCOLOR_VALUE( background );
    SET_ENTITYCOLOR_VALUE( text );

    // General values
    SET_VALUE_COLOR( linkTextColor );
    SET_VALUE_COLOR( linkBackgroundColor );
    SET_VALUE_COLOR( reflectiveLinkBackgroundColor );
    SET_VALUE_COLOR( reflectiveLinkTextColor );
    SET_VALUE_COLOR( assocGradientColor1 );
    SET_VALUE_COLOR( assocGradientColor2 );
    SET_VALUE_COLOR( cardinal1Color );
    SET_VALUE_COLOR( cardinal2Color );
    SET_VALUE_COLOR( roleColor );
    SET_VALUE_COLOR( lineColor );
    SET_VALUE_COLOR( paletteBackgroundColor );
    SET_VALUE_COLOR( paletteTextColor );
}

EntityColor Config::entityColor() const
{
    return _entityColor;
}

void Config::setEntityColor( const EntityColor& entityColor )
{
    _entityColor = entityColor;
}

QColor Config::getLinkTextColor() const
{
    return _linkTextColor;
}

void Config::setLinkTextColor( const QColor& linkTextColor )
{
    _linkTextColor = linkTextColor;
}

QColor Config::getLinkBackgroundColor() const
{
    return _linkBackgroundColor;
}

void Config::setLinkBackgroundColor( const QColor& linkBackgroundColor )
{
    _linkBackgroundColor = linkBackgroundColor;
}

QColor Config::getReflectiveLinkBackgroundColor() const
{
    return _reflectiveLinkBackgroundColor;
}

void Config::setReflectiveLinkBackgroundColor(
  const QColor& reflectiveLinkBackgroundColor )
{
    _reflectiveLinkBackgroundColor = reflectiveLinkBackgroundColor;
}

QColor Config::getReflectiveLinkTextColor() const
{
    return _reflectiveLinkTextColor;
}

void Config::setReflectiveLinkTextColor(
  const QColor& reflectiveLinkTextColor )
{
    _reflectiveLinkTextColor = reflectiveLinkTextColor;
}

QColor Config::getAssocGradientColor1() const
{
    return _assocGradientColor1;
}

void Config::setAssocGradientColor1( const QColor& assocGradientColor1 )
{
    _assocGradientColor1 = assocGradientColor1;
}

QColor Config::getAssocGradientColor2() const
{
    return _assocGradientColor2;
}

void Config::setAssocGradientColor2( const QColor& assocGradientColor2 )
{
    _assocGradientColor2 = assocGradientColor2;
}

QColor Config::getArrowColor() const
{
    return _arrowColor;
}

void Config::setArrowColor( const QColor& arrowColor )
{
    _arrowColor = arrowColor;
}

QColor Config::getLineColor() const
{
    return _lineColor;
}

void Config::setLineColor( const QColor& lineColor )
{
    _lineColor = lineColor;
}

QColor Config::getRoleColor() const
{
    return _roleColor;
}

void Config::setRoleColor( const QColor& roleColor )
{
    _roleColor = roleColor;
}

QColor Config::getCardinal1Color() const
{
    return _cardinal1Color;
}

void Config::setCardinal1Color( const QColor& cardinal1Color )
{
    _cardinal1Color = cardinal1Color;
}

QColor Config::getCardinal2Color() const
{
    return _cardinal2Color;
}

void Config::setCardinal2Color( const QColor& cardinal2Color )
{
    _cardinal2Color = cardinal2Color;
}


QColor Config::getPaletteBackgroundColor() const
{
    return _paletteBackgroundColor;
}

void Config::setPaletteBackgroundColor(const QColor& paletteBackgroundColor)
{
    _paletteBackgroundColor = paletteBackgroundColor;
}

QColor Config::getPaletteTextColor() const
{
    return _paletteTextColor;
}

void Config::setPaletteTextColor(const QColor& paletteTextColor)
{
    _paletteTextColor = paletteTextColor;
}
