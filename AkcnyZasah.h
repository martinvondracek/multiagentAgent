/* 
 * File:   AkcnyZasah.h
 * Author: root
 *
 * Created on Štvrtok, 2015, apríl 2, 16:36
 */

#ifndef AKCNYZASAH_H
#define	AKCNYZASAH_H

class AkcnyZasah {
public:
    AkcnyZasah(int rightWheel, int leftWheel, bool obchadzanie, int obchadzanieStav);
    
    int GetLeftWheel();
    void SetLeftWheel(int leftWheel);
    bool IsObchadzanie();
    void SetObchadzanie(bool obchadzanie);
    int GetObchadzanieStav();
    void SetObchadzanieStav(int obchadzanieStav);
    int GetRightWheel();
    void SetRightWheel(int rightWheel);

    static AkcnyZasah* stopWithObchadzanie(int obchadzanieStav);
    static AkcnyZasah* stopNotObchadzanie();
    
    virtual ~AkcnyZasah();
private:
    bool obchadzanie;
    int obchadzanieStav;
    
    int rightWheel;
    int leftWheel;
};

#endif	/* AKCNYZASAH_H */

