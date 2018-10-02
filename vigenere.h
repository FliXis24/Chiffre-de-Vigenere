#include <QtWidgets>

#ifndef VIGENERE_H
#define VIGENERE_H

class Vigenere : public QWidget {
    Q_OBJECT
private:
    //Алфавит
    static const QString BOARD;

    //Длина алфавита +1
    static const int BOARDEND;

    //Поля ввода и вывода дешифрованного и шифрованного текста
    QPlainTextEdit txtEdtDecrypted, txtEdtEnrypted;

    //Поле ввода ключа
    QLineEdit lnEdtKey;

    //Функция заполнения строки ключа до нужной длины
    //Во втором аргументе передается требуемая длина строки
    void fillkey(QString &key, int size);

public:
    Vigenere(QWidget *pwgt = nullptr);
    ~Vigenere();

public slots:
    //Функция-слот шифрования
    void slotButtonClickedEncrypt();

    //Функция-слот дешифрования
    void slotButtonClickedDecrypt();
};

#endif // VIGENERE_H
