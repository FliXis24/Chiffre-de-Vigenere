/**************************
*                         *
*   Chiffre de Vigenere   *
*                         *
**************************/

#include <QApplication>
#include <vigenere.h>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    //Создаем объект класса, наследуемого от QWidget
    Vigenere vigenere;

    vigenere.setWindowTitle("Chiffre de Vigenere");
    vigenere.show();

    return app.exec();
}
