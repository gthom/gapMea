#ifndef CONFIG_H
#define CONFIG_H

#include <QFile>
#include <QSettings>
#include <QCoreApplication>
#include <QRgb>

#include "entitycolor.h"

/**
 * @brief The Config class
 * Permits to configure gapMea colors in general (only entities for now)
 * Maybe doing a palette would be great.
 */
class Config
{
  private:
    /**
     * @brief entityColor
     * The colors that will be used for entity
     */
    EntityColor _entityColor;

    /**
     * @brief _fileName
     * The configuration's file name
     */
    QString _fileName;

  public:
    /**
     * @brief Config
     * Initialize/read the configuration file.
     */
    Config(const QString& fileName);
    /**
     * @brief refresh
     * Refreshes the configuration.
     */
    void refresh();
    /**
     * @brief save
     * Saves the configuration.
     */
    void save();
    /**
     * @brief entityColor
     * @return
     */
    EntityColor entityColor() const;
    /**
     * @brief setEntityColor
     * @param entityColor
     */
    void setEntityColor( const EntityColor& entityColor );

  public:
    /**
     * @brief singleton
     * @return
     * Creates a singleton of Config
     */
    static Config* singleton();
};

extern Config *g_pConfig, *config;

#endif // CONFIG_H
