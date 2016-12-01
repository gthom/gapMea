#ifndef XMEAREADER_H
#define XMEAREADER_H

#include <QXmlStreamReader>
#include "lien.h"
#include "entite.h"
#include "association.h"
#include "mainwindow.h"

/**
 * @brief The XMeaReader class
 * this is to read an xml  .mea file
 */
class XMeaReader : public QXmlStreamReader
{
private:
    MainWindow * mum;
public:
    /**
     * @brief XMeaReader
     * Constructor
     */
    XMeaReader(MainWindow *);
    /**
     * @brief readFile
     * @param device
     * @return true if file is ok
     */
    bool readFile(QIODevice* device);
    /**
     * @brief readMea
     * read MEA main content
     */
    void readMea();
    /**
     * @brief readEntites
     *read Entites Section
     */
    void readEntites();
    /**
     * @brief readEntite
     *read one Entity
     */
    void readEntite();
    /**
     * @brief readLiens
     *read Links Section
     */
    void readLiens();
    /**
     * @brief readLien
     *read one link
     */
    void readLien();  
    ///destructor
    ~XMeaReader();
    /**
     * @brief readFields
     * @param lEntite
     * read fields section of an entity
     */
    void readFields(Entite *lEntite);
    /**
     * @brief readField
     * @param lEntite
     *Read one field
     */
    void readField(Entite *lEntite);
};
#endif // XMEAREADER_H
