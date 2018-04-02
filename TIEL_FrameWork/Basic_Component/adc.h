//////////////////////////////////////////////////////////////////////////////////////////
 
// Project description
 
// Author: Yoo Joo-Hyoung (potato97@naver.com)
 
// Site: ccrs.hanyang.ac.kr
 
// Copyright (C) 2013-2013 TIEF(TIEF is Embedded S/W Framework) Project.
 
//
 
//////////////////////////////////////////////////////////////////////////////////////////
//
//    License type: GNU General Public License (GPL)
//      
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ADC_H__
#define	__ADC_H__

//���: ��������(��Ȯ�� ���ø� �ֱ⸦ �����ϱ�����), �̸��극�̼��� ����,�������ø�,�ñ׳� ����ȭ?, ���������̼� ��...
//�׸��� ��� ������ adc�� � �� �� �ֵ��� �߻�ȭ�ؾ���.(�ִ� 16bit ADC���� ��)
//���� ����̽� ����̹��� ������ �߻�ȭ�Ͽ�,
//���ø����̼��� �ڵ尡 ������ ���ɼ��� �ּ�ȭ�ؾ���.
//������ ���� ����̹��� ����� �ٲ𰡴ɼ��� ŭ
//��) ��ŷ -> ���ŷ

#include "TimerManager.h"

class AdcEvent;
class Adc;

class IAdcPort
{
  friend class Adc;
public:
  IAdcPort(){}
  virtual ~IAdcPort(){}

protected:
  virtual unsigned char isConverted(void) = 0;
  virtual unsigned short GetAdc(void) = 0;
};



class Adc: public ITimerEvent
{
  AdcEvent *ev;
  IAdcPort * iadc;
public:
  Adc(IAdcPort * _iadc);
  virtual ~Adc();
  
    void Run(void);
    void Stop(void);
    void SetFrequency(unsigned char _Hz);
//  unsigned char SetFrequency(unsigned char _Hz);
    void Addevent(AdcEvent * _ev);
//  char SetChannelEvent(unsigned char _ch, AdcEvent * _ev);
//  unsigned char GetAdc(unsigned char _Channel);
//  unsigned short GetAdc(unsigned char _Channel);
//  unsigned short GetAdc(void);

private:
    void evTick(void);
    void  TimeOutEvent(void);
    

};

class AdcEvent{
friend class Adc;

public:
  AdcEvent(){}
  virtual ~AdcEvent(){}
protected:

//virtual void Converted(unsigned char _ch, unsigned short _valueOfAdc) = 0;

virtual void Converted( unsigned short _valueOfAdc) = 0;
  
};

class AdcCalibrationTable{

//�̸��극�̼� ������ �Է�  
};
#endif