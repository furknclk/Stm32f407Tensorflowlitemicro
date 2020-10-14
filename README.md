# Stm32f407Tensorflowlitemicro
stm32f407vg discovery kart üzerinde Tensorflow Lite Micro HelloWorld  uygulaması

İndirdiğiniz kütüphaneleri Kaynak kodlar ile aynı dizine koymanız yeterli.Adresleri ile ilgi tanımlama proje dosyasında yapıldı. Çalıştırılan örnek tflite modeli Pete warden tarafından yazılan tinyMl kitabındaki HelloWorld uygulamasıdır. Debug consolu stm32f407 üzerinde çalışabilecek şekilde değiştirildi.

Model hakkında ::
Model radyan cinsinden girilen açı değerlerinin sinüs fonksiyonundaki karşılığını tahmin etmek üzere eğitilmiştir. Modelden elde edilen tahminler kart üzerindeki d4 pinine PWM sinyali olarak uygulanmıştır. Eğiteceğiniz farklı bir model de problemsiz çalışacaktır.
