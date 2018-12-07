#ifndef IWIDGET_H
#define IWIDGET_H

#include "dataBuffer.h"

/*!
 * \brief The IWidget class
 */
class IWidget
{
public:
    /*!
     * \brief IWidget
     */
    IWidget(){}
    virtual ~IWidget(){ }

    /*!
     * \brief displayMsg
     * \param tag
     * \param msg
     */
    virtual void displayMsg(std::string tag, std::string msg)=0;

    /*!
     * \brief setData
     * \param data
     */
    virtual void setData(DataBufferPtr data)=0;

};

#endif // IWIDGET_H
