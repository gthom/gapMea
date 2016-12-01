#ifndef XMEAWRITER_H
#define XMEAWRITER_H

#include <QXmlStreamWriter>
#include "lien.h"
#include "entite.h"
#include "mainwindow.h"

/**
 * @brief The XMeaWriter class
 * this class is used to write xml mea file
 */
class XMeaWriter : public QXmlStreamWriter
{
private:
    MainWindow * mum;
public:
    /**
     * @brief XMeaWriter
     * @param maman
     * Constructor
     */
    XMeaWriter(MainWindow* maman);
    ///destructor
    ~XMeaWriter();
    /**
     * @brief writeEntites
     * Write all entities
     */
    void writeEntites();
    /**
     * @brief writeEntite
     *Write one entity
     */
    void writeEntite(Entite*);
    /**
     * @brief writeLiens
     * Write all links
     */
    void writeLiens();
    /**
     * @brief writeLien
     *Write One link
     */
    void writeLien(Lien*);
    /**
     * @brief writeMea
     * Write Mea section( main container)
     */
    void writeMea();
    /**
     * @brief writeFile
     * @param device
     * @return generally true false if filesystem connot be written
     * write the xml .mea file
     */
    bool writeFile(QIODevice *device);
};
#endif // XMEAWRITER_H
