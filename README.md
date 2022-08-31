# dino-AI
 
Использование эволюционного алгоритма и нейронной сети, на примере игры google динозаврик (только тут у динозаврика двойной прыжок). 

 В файле globals можно менять глобальные параметры приложения. Программа создает популяцию динозавриков (размера populationSize (чем больше populationSize тем быстрее учатся динозаврики, но медленнее работает программа)), у каждого динозаврика свой "мозг". Когда все динозаврики умрут, программа выбирает лучших и из них создает новую популяцию (также алгоритм определяет схожесть поведения особей и засовывает их в разные виды). В новой популяции будут и мутировавшие особи для сохранения видового разнообразия (чтобы не застрять в развитии). Так же в вышеупомянутом globals.h можно найти шансы мутаций и поэксперементировать с ними. В программе есть возможность для сохранения истории мутаций.
 
 С течением времени препятствия ускоряются, на счете около 2500 они двигаются настолько быстро, что коллизия не успевает срабатывать, это считается концом игры.

(утечки памяти - мое почтение)
