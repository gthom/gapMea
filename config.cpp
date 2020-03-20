#include "config.h"

#define GET_ENTITYCOLOR_VALUE( val ) settings.value( "entityColor/" #val )

#define SET_ENTITYCOLOR_VALUE( name, val )                               \
    settings.setValue( "entityColor/" #name, val )

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

    // Load configuration if it exists
    if ( settings.allKeys().size() )
    {
        _entityColor.setTitleBackground(
          GET_ENTITYCOLOR_VALUE( titleBackground ).value< QColor >() );
        _entityColor.setBackground(
          GET_ENTITYCOLOR_VALUE( background ).value< QColor >() );
        _entityColor.setText(
          GET_ENTITYCOLOR_VALUE( text ).value< QColor >() );
    }
    else // Otherwhise write default configuration
    {
        SET_ENTITYCOLOR_VALUE( titleBackground,
                               _entityColor.titleBackground().name() );
        SET_ENTITYCOLOR_VALUE( background,
                               _entityColor.background().name() );
        SET_ENTITYCOLOR_VALUE( text, _entityColor.text().name() );
    }
}

void Config::save()
{
    QSettings settings( _fileName, QSettings::Format::IniFormat );

    SET_ENTITYCOLOR_VALUE( titleBackground,
                           _entityColor.titleBackground().name() );
    SET_ENTITYCOLOR_VALUE( background, _entityColor.background().name() );
    SET_ENTITYCOLOR_VALUE( text, _entityColor.text().name() );
}

EntityColor Config::entityColor() const
{
    return _entityColor;
}

void Config::setEntityColor( const EntityColor& entityColor )
{
    _entityColor = entityColor;
}
