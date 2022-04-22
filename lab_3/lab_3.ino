float voltage[]= {0,0,0,0,0};
float avgVoltage[]= {0,0,0,0,0};


void setup() {
  // put your setup code here, to run once:
  for(int i = 8; i< 12;i++)
    pinMode(i, OUTPUT);
  Serial.begin(9600);
}

//кальман

float simpleKalman(float newVal) {
  static float _err_measure = 0.8;  // примерный шум измерений
  static float _q = 0.5;   // скорость изменения значений 0.001-1, варьировать самому
  float _kalman_gain, _current_estimate;
  static float _err_estimate = _err_measure;
  static float _last_estimate;
  _kalman_gain = (float)_err_estimate / (_err_estimate + _err_measure);
  _current_estimate = _last_estimate + (float)_kalman_gain * (newVal - _last_estimate);
  _err_estimate =  (1.0 - _kalman_gain) * _err_estimate + fabs(_last_estimate - _current_estimate) * _q;
  _last_estimate = _current_estimate;
  return _current_estimate;
}


float runMiddleArifmOptim(float newVal) {
  static int t = 0;
  static float vals[10];
  static float average = 0;
  if (++t >= 10) t = 0; // перемотка t
  average -= vals[t];         // вычитаем старое
  average += newVal;          // прибавляем новое
  vals[t] = newVal;           // запоминаем в массив
  return ((float)average / 10);
}

int median(int newVal) {
  static int buf[3];
  static byte count = 0;
  buf[count] = newVal;
  if (++count >= 3) count = 0;
  return (max(buf[0], buf[1]) == max(buf[1], buf[2])) ? max(buf[0], buf[2]) : max(buf[1], min(buf[0], buf[2]));
}

float dt = 0.02;
float sigma_process = 3.0;
float sigma_noise = 0.7;


float ABfilter(float newVal) {
  static float xk_1, vk_1, a, b;
  static float xk, vk, rk;
  static float xm;
  float lambda = (float)sigma_process * dt * dt / sigma_noise;
  float r = (4 + lambda - (float)sqrt(8 * lambda + lambda * lambda)) / 4;
  a = (float)1 - r * r;
  b = (float)2 * (2 - a) - 4 * (float)sqrt(1 - a);
  xm = newVal;
  xk = xk_1 + ((float) vk_1 * dt );
  vk = vk_1;
  rk = xm - xk;
  xk += (float)a * rk;
  vk += (float)( b * rk ) / dt;
  xk_1 = xk;
  vk_1 = vk;
  return xk_1;
}


float k = 0.1;  // коэффициент фильтрации, 0.0-1.0
// бегущее среднее
float expRunningAverage(float newVal) {
  static float filVal = 0;
  filVal += (newVal - filVal) * k;
  return filVal;
}


float toVoltage(int dat){
  return (float)(dat * 5.0) / 1024;
}




void loop() {
  
  for(int i = 0;i<5;i++){
    voltage[i]=toVoltage(analogRead(i));
    //Serial.println(voltage[i]);
  }

  avgVoltage[0]=runMiddleArifmOptim(voltage[0]);
  avgVoltage[1]=median(voltage[1]);
  avgVoltage[2]=simpleKalman(voltage[2]);
  avgVoltage[3]=ABfilter(voltage[3]);
  avgVoltage[4]=expRunningAverage(voltage[4]);

  if(avgVoltage[1]>avgVoltage[2])
    digitalWrite(8, HIGH);
  else
    digitalWrite(8, LOW);


  if(avgVoltage[3]>avgVoltage[4]+1.5)
    digitalWrite(9, HIGH);
  else
    digitalWrite(9, LOW);


  if(avgVoltage[0]>avgVoltage[1]+avgVoltage[2])
    digitalWrite(10, HIGH);
  else
    digitalWrite(10, LOW);


  if(avgVoltage[1]<avgVoltage[4])
    digitalWrite(11, HIGH);
  else
    digitalWrite(11, LOW);


  if(abs(avgVoltage[0] - voltage[0]) > 0.1){
    Serial.println("runMiddleArifmOptim");
    Serial.println(voltage[0]);
    Serial.println(avgVoltage[0]);
    Serial.println("");
  }
  if(abs(avgVoltage[1] - voltage[1]) > 0.1){
    Serial.println("median");
    Serial.println(voltage[1]);
    Serial.println(avgVoltage[1]);
    Serial.println("");
  }
  if(abs(avgVoltage[2] - voltage[2]) > 0.1){
    Serial.println("kalman");
    Serial.println(voltage[2]);
    Serial.println(avgVoltage[2]);
    Serial.println("__");
  }
  //voltage[0]toVoltage(analogRead(0)));
  
  Serial.println("_____________");
  delay(400);

}
