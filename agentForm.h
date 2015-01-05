/* 
 * File:   agentForm.h
 * Author: root
 *
 * Created on Pondelok, 2015, január 5, 23:36
 */

#ifndef _AGENTFORM_H
#define	_AGENTFORM_H

#include "ui_agentForm.h"

class agentForm : public QDialog {
    Q_OBJECT
public:
    agentForm();
    virtual ~agentForm();
private:
    Ui::agentForm widget;
};

#endif	/* _AGENTFORM_H */
