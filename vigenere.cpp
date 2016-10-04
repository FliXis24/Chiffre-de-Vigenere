#include <vigenere.h>

//Инициализация алфавита
const QString Vigenere::BOARD = " !\"#$%&'()*+,-./0123456789:;<=>?@"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`"
                                "abcdefghijklmnopqrstuvwxyz{|}~"
                                "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                                "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

//Инициализация длиной алфавита +1
const int Vigenere::BOARDEND = BOARD.length();

Vigenere::Vigenere(QWidget* pwgt/*= 0*/) : QWidget(pwgt) {
    //Создаем три текстовые метки
    QLabel *lblTextEncrypted = new QLabel("Encrypt text:");
    QLabel *lblTextDecrypted = new QLabel("Decrypt text:");
    QLabel *lblTextKey = new QLabel("Key:");

    //Кнопки для шифрования и дешифрования
    QPushButton *btnEncrypt = new QPushButton(">>");
    QPushButton *btnDecrypt = new QPushButton("<<");

    //Подключаем сигнал из кнопки шифрования к слоту
    connect(btnEncrypt, SIGNAL(clicked()),
            SLOT(slotButtonClickedEncrypt())
            );

    //Подключаем сигнал из кнопки дешифрования к слоту
    connect(btnDecrypt, SIGNAL(clicked()),
            SLOT(slotButtonClickedDecrypt())
            );

    //Создаем вертикальные и горизонтальные менеджеры компоновки
    //Этот будет базовым для всех остальных
    QHBoxLayout *hblBase = new QHBoxLayout;

    //Это побочные
    QHBoxLayout *hblKey = new QHBoxLayout;
    QVBoxLayout *vblDec = new QVBoxLayout;
    QVBoxLayout *vblButKey = new QVBoxLayout;
    QVBoxLayout *vblEnc = new QVBoxLayout;

    //Заносим текстовую метку и поле ввода дешифрованного текста
    vblDec->addWidget(lblTextDecrypted);
    vblDec->addWidget(&txtEdtDecrypted);

    //Заносим кнопку шифрования
    vblButKey->addStretch(2);
    vblButKey->addWidget(btnEncrypt);
    vblButKey->addStretch(1);

    //Заносим текстовую метку и поле ввода ключа
    hblKey->addWidget(lblTextKey);
    hblKey->addWidget(&lnEdtKey);
    //Добавим в него горизонтальный менеджер для ключей
    vblButKey->addLayout(hblKey);

    //Заносим кнопку дешифрования
    vblButKey->addStretch(1);
    vblButKey->addWidget(btnDecrypt);
    vblButKey->addStretch(2);

    //Заносим текстовую метку и поле ввода шифрованного текста
    vblEnc->addWidget(lblTextEncrypted);
    vblEnc->addWidget(&txtEdtEnrypted);

    //Добавляем побочные менеджеры в базовый
    hblBase->addLayout(vblDec);
    hblBase->addLayout(vblButKey);
    hblBase->addLayout(vblEnc);

    //Устанавливаем наш базовый менеджер компоновки
    setLayout(hblBase);
}
Vigenere::~Vigenere() {}

//Функция заполнения строки ключа до нужной длины
//В аргументе передается требуемая длина строки
void Vigenere::fillkey(int size) {
    for(int i = key.length(), j = 0; i < size; ++i, ++j)
        //Заполняем строку ключа самой собой, до тех пор, пока длина ключа не сравняется с
                                                    //требуемой длиной строки из аргумента
        key[i] = key[j];
}

//Функция очистки строк
void Vigenere::clean() {
    //Проверяем на пустоту, если не пусто, то очищаем содержимое строк
    if(!encrypted.isEmpty())
        encrypted.resize(0);
    if(!decrypted.isEmpty())
        decrypted.resize(0);
    if(!key.isEmpty())
        key.resize(0);
}

//Функция-слот шифрования
void Vigenere::slotButtonClickedEncrypt() {
    //Очищаем строки
    clean();

    /*Получаем, введенный пользователем, дешифрованный текст и ключ из полей, записываем их
                                                                                 в строки*/
    decrypted.append(txtEdtDecrypted.toPlainText());
    key.append(lnEdtKey.text());

    //Проверяем длину строки ключа
    if(decrypted.size() > key.size())
        //Если она меньше длины дешифрованного текста, заполняем до необходимой длины
        fillkey(decrypted.size());

    //Шифрование
    for(int i = 0, j = 0; i < decrypted.length(); ++i, ++j) {
        /*Получаем порядковые номера символов относительно алфавита из строк с ключем и
                                                                дешифрованного текста*/
        int tempDecrypted = BOARD.indexOf(decrypted[i]);
        int tempKey = BOARD.indexOf(key[j]);

        //Функция indexOf возвращает -1, если символ не найден в алфавите
        if(tempDecrypted < 0 || tempKey < 0) {
            /*Пропускаем некорректный символ, предварительно компенсировав счетчик ключа,
              если этого не сделать, то результат последующего дешифрования этого текста
                                                                         будет не верен*/
            --j;
            continue;
        }
        //Записываем, полученный по формуле, символ в строку для шифрованного текста
        encrypted += BOARD.at((tempDecrypted + tempKey) % BOARDEND);
    }
    //Отображаем результат шифрования в поле для шифрованного текста
    txtEdtEnrypted.setPlainText(encrypted);
}

//Функция-слот дешифрования
void Vigenere::slotButtonClickedDecrypt() {
    //Очищая строки
    clean();

    /*Получаем, введенный пользователем, дешифрованный текст и ключ из полей, записываем их
                                                                                 в строки*/
    encrypted.append(txtEdtEnrypted.toPlainText());
    key.append(lnEdtKey.text());

    //Проверяем длину строки ключа
    if(encrypted.size() > key.size())
        //Если она меньше длины шифрованного текста, заполняем до необходимой длины
        fillkey(encrypted.size());

    //Дешифрование
    for(int i = 0, j = 0; i < encrypted.length(); ++i, ++j) {
        /*Получаем порядковые номера символов относительно алфавита из строк с ключем и
                                                                  шифрованного текста*/
        int tempEncrypted = BOARD.indexOf(encrypted[i]);
        int tempKey = BOARD.indexOf(key[j]);

        //Функция indexOf возвращает -1, если символ не найден в алфавите
        if(tempEncrypted < 0 || tempKey < 0) {
            /*Пропускаем некорректный символ, предварительно компенсировав счетчик ключа,
              если этого не сделать, то результат последующего шифрования этого текста
                                                                          будет не верен*/
            --j;
            continue;
        }
        //Записываем, полученный по формуле, символ в строку для дешифрованного текста
        decrypted += BOARD.at((tempEncrypted - tempKey + BOARDEND) % BOARDEND);
    }
    //Отображаем результат дешифрования в поле для дешифрованного текста
    txtEdtDecrypted.setPlainText(decrypted);
}
