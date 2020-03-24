#include "config.h"

#define SET_ENTITYCOLOR_VALUE( val )                                     \
    settings.setValue( "entityColor/" #val, _entityColor.val().name() )

#define GET_ENTITYCOLOR_VALUE( val )                                     \
    settings.value( "entityColor/" #val ).value< QColor >()

#define SET_VALUE_COLOR( field )                                         \
    settings.setValue( "generalColor/" #field, _##field.name() )

#define GET_VALUE_COLOR( val )                                           \
    if ( settings.contains( "entityColor/" #val ) )                      \
    {                                                                    \
        _##val                                                           \
          = settings.value( "generalColor/" #val ).value< QColor >();    \
    }                                                                    \
    else                                                                 \
    {                                                                    \
        SET_VALUE_COLOR( val );                                          \
    }

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
    // Get config values, if cannot we write the original values to the
    // cfg file.
    getValues();

    // Always put the new values inside the configuration file.
    setValues();
}

void Config::save()
{
    setValues();
}

void Config::getValues()
{
    QSettings settings( _fileName, QSettings::Format::IniFormat );

    // Entity color color values
    if ( settings.contains( "entityColor/titleBackground" ) )
    {
        _entityColor.setTitleBackground(
          GET_ENTITYCOLOR_VALUE( titleBackground ) );
    }
    else
    {
        SET_ENTITYCOLOR_VALUE( titleBackground );
    }

    if ( settings.contains( "entityColor/background" ) )
    {
        _entityColor.setBackground( GET_ENTITYCOLOR_VALUE( background ) );
    }
    else
    {
        SET_ENTITYCOLOR_VALUE( background );
    }

    if ( settings.contains( "entityColor/text" ) )
    {
        _entityColor.setText( GET_ENTITYCOLOR_VALUE( text ) );
    }
    else
    {
        SET_ENTITYCOLOR_VALUE( text );
    }

    // General color color values
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
    GET_VALUE_COLOR( sqlGenEntityNameColor );
    GET_VALUE_COLOR( sqlGenEntityReservedColor );
    GET_VALUE_COLOR( sqlGenPropertyNameColor );
    GET_VALUE_COLOR( sqlGenPropertySizeColor );
    GET_VALUE_COLOR( sqlGenPropertyTypeColor );
}

void Config::setValues()
{
    QSettings settings( _fileName, QSettings::Format::IniFormat );

    // Entity color values
    SET_ENTITYCOLOR_VALUE( titleBackground );
    SET_ENTITYCOLOR_VALUE( background );
    SET_ENTITYCOLOR_VALUE( text );

    // General color values
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
    SET_VALUE_COLOR( sqlGenEntityNameColor );
    SET_VALUE_COLOR( sqlGenEntityReservedColor );
    SET_VALUE_COLOR( sqlGenPropertyNameColor );
    SET_VALUE_COLOR( sqlGenPropertySizeColor );
    SET_VALUE_COLOR( sqlGenPropertyTypeColor );
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

void Config::setPaletteBackgroundColor(
  const QColor& paletteBackgroundColor )
{
    _paletteBackgroundColor = paletteBackgroundColor;
}

QColor Config::getPaletteTextColor() const
{
    return _paletteTextColor;
}

void Config::setPaletteTextColor( const QColor& paletteTextColor )
{
    _paletteTextColor = paletteTextColor;
}

QColor Config::getSqlGenEntityReservedColor() const
{
    return _sqlGenEntityReservedColor;
}

void Config::setSqlGenEntityReservedColor(
  const QColor& sqlGenEntityReservedColor )
{
    _sqlGenEntityReservedColor = sqlGenEntityReservedColor;
}

QColor Config::getSqlGenEntityNameColor() const
{
    return _sqlGenEntityNameColor;
}

void Config::setSqlGenEntityNameColor( const QColor& sqlGenEntityNameColor )
{
    _sqlGenEntityNameColor = sqlGenEntityNameColor;
}

QColor Config::getSqlGenPropertyTypeColor() const
{
    return _sqlGenPropertyTypeColor;
}

void Config::setSqlGenPropertyTypeColor(
  const QColor& sqlGenPropertyTypeColor )
{
    _sqlGenPropertyTypeColor = sqlGenPropertyTypeColor;
}

QColor Config::getSqlGenPropertyNameColor() const
{
    return _sqlGenPropertyNameColor;
}

void Config::setSqlGenPropertyNameColor(
  const QColor& sqlGenPropertyNameColor )
{
    _sqlGenPropertyNameColor = sqlGenPropertyNameColor;
}

QColor Config::getSqlGenPropertySizeColor() const
{
    return _sqlGenPropertySizeColor;
}

void Config::setSqlGenPropertySizeColor(
  const QColor& sqlGenPropertySizeColor )
{
    _sqlGenPropertySizeColor = sqlGenPropertySizeColor;
}
