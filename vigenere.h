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

    //Строки для хранения дешифрованного, шифрованного текста, и ключа
    QString decrypted, encrypted, key;

    //Поля ввода и вывода дешифрованного и шифрованного текста
    QPlainTextEdit txtEdtDecrypted, txtEdtEnrypted;

    //Поле ввода ключа
    QLineEdit lnEdtKey;

    //Функция заполнения строки ключа до нужной длины
    //В аргументе передается требуемая длина строки
    void fillkey(int size);

    //Функция очистки строк
    void clean();

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
