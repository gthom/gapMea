#ifndef ENTITYCOLOR_H
#define ENTITYCOLOR_H

#include <QColor>

/**
 * @brief The EntityColor class
 *  Entity color that will be used into the html code
 *  for Entite::getkeyAsForeignKey
 */
class EntityColor
{
  private:
    /**
     * @brief _titleBackground
     * The color of title's background.
     */
    QColor _titleBackground;
    /**
     * @brief _background
     * The color of the general background
     */
    QColor _background;
    /**
     * @brief _text
     * The color of the text
     */
    QColor _text;

  public:
    /**
     * @brief EntityColor
     * Default constructor
     */
    EntityColor();
    /**
     * @brief EntityColor
     * @param titleBackground
     * @param background
     * @param text
     */
    EntityColor( const QColor& titleBackground,
                 const QColor& background,
                 const QColor& text );

  public:
    /**
     * @brief titleBackground
     * @return
     */
    QColor titleBackground() const;
    /**
     * @brief setTitleBackground
     * @param titleBackground
     */
    void setTitleBackground( const QColor& titleBackground );
    /**
     * @brief background
     * @return
     */
    QColor background() const;
    /**
     * @brief setBackground
     * @param background
     */
    void setBackground( const QColor& background );
    /**
     * @brief text
     * @return
     */
    QColor text() const;
    /**
     * @brief setText
     * @param text
     */
    void setText( const QColor& text );
};

#endif // ENTITYCOLOR_H
