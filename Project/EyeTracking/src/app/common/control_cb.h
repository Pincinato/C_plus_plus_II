/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#ifndef CONTROL_CB_H
#define CONTROL_CB_H


#include <QString>
#include "dataBuffer.h"

/*!
 * \brief The HostCb class Abstract Interface for Control implemented by the host / widget-UI.
 * Implements Info, error and data callbacks.
 */
class ControlCB
{
public:
    virtual void host_data_cb( DataBufferPtr data ) = 0;
    virtual void host_info_cb( const QString& tag, const QString& msg ) = 0;
    virtual void host_error_cb( const QString& tag, const QString& err ) = 0;

};

#endif // CONTROL_CB_H
