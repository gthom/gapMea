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
    /**
     * @brief _linkTextColor
     */
    QColor _linkTextColor = Qt::black;
    /**
     * @brief _linkBackgroundColor
     */
    QColor _linkBackgroundColor = QColor( "#4949FF" );
    /**
     * @brief _reflectiveLinkBackgroundColor
     */
    QColor _reflectiveLinkBackgroundColor = QColor( "#4949FF" );
    /**
     * @brief _reflectiveLinkTextColor
     */
    QColor _reflectiveLinkTextColor = Qt::black;
    /**
     * @brief _assocGradientColor1
     */
    QColor _assocGradientColor1 = QColor( "#4949FF" );
    /**
     * @brief _assocGradientColor2
     */
    QColor _assocGradientColor2 = Qt::white;
    /**
     * @brief _arrowColor
     */
    QColor _arrowColor = Qt::white;
    /**
     * @brief _lineColor
     */
    QColor _lineColor = Qt::white;
    /**
     * @brief _roleColor
     */
    QColor _roleColor = Qt::white;
    /**
     * @brief _cardinal1Color
     */
    QColor _cardinal1Color = Qt::white;
    /**
     * @brief _cardinal2Color
     */
    QColor _cardinal2Color = Qt::white;
    /**
     * @brief _paletteBackgroundColor
     */
    QColor _paletteBackgroundColor = Qt::lightGray;
    /**
     * @brief _paletteTextColor
     */
    QColor _paletteTextColor = Qt::black;

  public:
    /**
     * @brief Config
     * Initialize/read the configuration file.
     */
    Config( const QString& fileName );
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
     * @brief getValues
     * Get configuration values.
     */
    void getValues();
    /**
     * @brief setValues
     * Set configuration values.
     */
    void setValues();
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
    QColor getLinkTextColor() const;
    void setLinkTextColor( const QColor& linkTextColor );
    QColor getLinkBackgroundColor() const;
    void setLinkBackgroundColor( const QColor& linkBackgroundColor );
    QColor getReflectiveLinkBackgroundColor() const;
    void setReflectiveLinkBackgroundColor(
      const QColor& reflectiveLinkBackgroundColor );
    QColor getReflectiveLinkTextColor() const;
    void setReflectiveLinkTextColor( const QColor& reflectiveLinkTextColor );
    QColor getAssocGradientColor1() const;
    void setAssocGradientColor1( const QColor& assocGradientColor1 );
    QColor getAssocGradientColor2() const;
    void setAssocGradientColor2( const QColor& assocGradientColor2 );
    QColor getArrowColor() const;
    void setArrowColor(const QColor& arrowColor);
    QColor getLineColor() const;
    void setLineColor(const QColor& lineColor);
    QColor getRoleColor() const;
    void setRoleColor(const QColor& roleColor);
    QColor getCardinal1Color() const;
    void setCardinal1Color(const QColor& cardinal1Color);
    QColor getCardinal2Color() const;
    void setCardinal2Color(const QColor& cardinal2Color);
    QColor getPaletteBackgroundColor() const;
    void setPaletteBackgroundColor(const QColor& paletteBackgroundColor);
    QColor getPaletteTextColor() const;
    void setPaletteTextColor(const QColor& paletteTextColor);
};

extern Config *g_pConfig, *config;

#endif // CONFIG_H
