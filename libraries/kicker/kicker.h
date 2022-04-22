#ifndef __KICKER__
#define __KICKER__

class kicker{
  public:
    kicker(int k_pin,int ft_pin,int led_pin,int th_val,int delay_time);
    void setup();
    bool scan();
    void kick();

  private:
    int K_PIN,FT_PIN,LED_PIN,TH_VAL,DELAY_TIME;
};

#endif
