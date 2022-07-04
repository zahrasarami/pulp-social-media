#include "setting.h"
#include "ui_setting.h"
#include "customshadoweffect.h"
#include <QMessageBox>
#include <QFileDialog>

Setting::Setting(user me ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    howAmI = me;

    ui->usernameeditprofile->setReadOnly(true);
    ui->phoneeditprofile->setReadOnly(true);
    ui->emaileditprofile->setReadOnly(true);
    ui->winstack->setCurrentIndex(0);
    ui->userusernameforsettinglbl->setText(howAmI.get_UserName());
    picDir = QCoreApplication::applicationDirPath()+"/../"+QString::number(howAmI.get_ID())+".png";
    ui->profilepicture_2->setPixmap(QPixmap(picDir));
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(20.0);
    bodyShadow->setDistance(4.0);
    bodyShadow->setColor(QColor(10, 5, 45, 80));
    ui->winstack->setGraphicsEffect(bodyShadow);


}

Setting::~Setting()
{

    delete ui;
}

void Setting::on_editprofile_clicked()
{
    ui->winstack->setCurrentIndex(1);
    ui->Status->clear();

    QIntValidator* intValidator = new QIntValidator;
    ui->phoneeditprofile->setValidator(intValidator);


    ui->profilepictureeditprofile->setPixmap(QPixmap(picDir));
    ui->userideditprofile->setText(QString::number(howAmI.get_ID()));
    ui->firstnameeditprofile->setText(howAmI.get_firstname());
    ui->bioeditprofile->setText(howAmI.get_Bio());
    ui->passwordeditprofile->setText(howAmI.get_Password());
    ui->usernameeditprofile->setText(howAmI.get_UserName());
    ui->lastnameeditprofile->setText(howAmI.get_lastname());
    ui->phoneeditprofile->setText(howAmI.get_PhoneNumber());
    ui->emaileditprofile->setText(howAmI.get_EmailAddress());
    QDate Date = QDate::fromString(howAmI.get_BirthDate(),"M/d/yyyy");
    qDebug() << Date;
    ui->birthdateeditprofile->setDate(Date);
}


void Setting::on_backtohomepage_clicked()
{
    Setting::hide();
}


void Setting::on_backbtn_clicked()
{
    ui->winstack->setCurrentIndex(0);
}


void Setting::on_editprivacy_clicked()
{
    ui->winstack->setCurrentIndex(2);


    ui->showusername_2->setCurrentIndex(howAmI.getNameAccessibility());
    ui->showpicture_2->setCurrentIndex(howAmI.getPhotoAccessibility());
    ui->showemail_2->setCurrentIndex(howAmI.getEmailAccessibility());
    ui->showphonenumber_2->setCurrentIndex(howAmI.getPhoneAccessibility());
    ui->showfirstname_2->setCurrentIndex(howAmI.getFirstNameAccessibility());
    ui->showlastname_2->setCurrentIndex(howAmI.getLastNameAccessibility());
    ui->showbio_2->setCurrentIndex(howAmI.getBioAccessibility());
}


void Setting::on_backbtn_2_clicked()
{
    ui->winstack->setCurrentIndex(0);
}


void Setting::on_showpassforeditprofile_stateChanged(int arg1)
{
    if(arg1)
        ui->passwordeditprofile->setEchoMode(QLineEdit::Normal);
    else
        ui->passwordeditprofile->setEchoMode(QLineEdit::Password);
}


void Setting::on_savebtn_clicked()
{
    bool halt = false;


    if(ui->passwordeditprofile->text() == "")
    {
        ui->passwordeditprofile->setPlaceholderText("Password EMPTY!");
        halt = true;
    }

    if(ui->firstnameeditprofile->text() == "")
    {
        ui->firstnameeditprofile->setPlaceholderText("First Name EMPTY!");
        halt = true;
    }

    if(ui->lastnameeditprofile->text() == "")
    {
        ui->lastnameeditprofile->setPlaceholderText("Last Name EMPTY!");
        halt = true;
    }


    if(halt)
    {
        ui->Status->setText("<b color:#33>Please correct your mistakes.</b>");
    }
    else
    {
        QString password, firstname, lastname, bio, birthdate;
        password = ui->passwordeditprofile->text();
        firstname = ui->firstnameeditprofile->text();
        lastname = ui->lastnameeditprofile->text();
        bio = ui->bioeditprofile->text();
        birthdate = ui->birthdateeditprofile->text();

        if(password.size() < 4)
        {
            ui->passwordeditprofile->clear();
            QMessageBox::warning(this, "Warnning", "password must have at least 4 characters");
        }
        bool hasUppercase = false;
        bool hasNumber = false;
        for (int x = 0; x < password.length(); x++)
        {
            if (password[x] >= 'A' && password[x] < 'Z')
            {
                hasUppercase = true;
            }
            if (password[x] >= '0' && password[x] < '9')
            {
                hasNumber = true;
            }
        }
        // condition to check if password met the 2 requirements for including an uppercase letter and a number
        if (!hasNumber || !hasUppercase)
        {
            QMessageBox::warning(this,"Warning", "Password must include atleast 1 uppercase letter and atleast 1 number");
            ui->passwordeditprofile->clear();
        }

        bool password1;
        password1 = ui->passwordeditprofile->text().size();

        if(password1)
        {
            howAmI.set_Password(password);
            howAmI.set_Firstname(firstname);
            howAmI.set_Lastname(lastname);
            howAmI.set_Bio(bio);
            howAmI.set_BirthDate(birthdate);

            maindatabase::Modify_UserDetails(howAmI);


            if (this->picName_2 != "")
            {
                QString to = picDir;

                if (QFile::exists(to))
                {
                    QFile::remove(to);
                }
                QString path = QString::number(howAmI.get_ID()) + ".png";
                ui->profilepictureeditprofile->grab().save(path);
                ui->profilepicture_2->setText("<img src=\"file:///"+this->picName_2+"\" alt=\"Image read error!\" height=\"110\" width=\"110\" />");
            }

            ui->Status->setText("Edited successfully");

            QTime dieTime= QTime::currentTime().addSecs(2);
            while (QTime::currentTime() < dieTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

            on_backbtn_clicked();

        }
    }
}


void Setting::on_setonlyfreindsbtn_clicked()
{
    ui->showpicture_2->setCurrentIndex(1);
    ui->showusername_2->setCurrentIndex(1);
    ui->showphonenumber_2->setCurrentIndex(1);
    ui->showemail_2->setCurrentIndex(1);
    ui->showfirstname_2->setCurrentIndex(1);
    ui->showlastname_2->setCurrentIndex(1);
    ui->showbio_2->setCurrentIndex(1);
}


void Setting::on_settonoonebtn_clicked()
{
    ui->showpicture_2->setCurrentIndex(2);
    ui->showusername_2->setCurrentIndex(2);
    ui->showphonenumber_2->setCurrentIndex(2);
    ui->showemail_2->setCurrentIndex(2);
    ui->showfirstname_2->setCurrentIndex(2);
    ui->showlastname_2->setCurrentIndex(2);
    ui->showbio_2->setCurrentIndex(2);
}


void Setting::on_resettodefault_clicked()
{
    ui->showpicture_2->setCurrentIndex(0);
    ui->showusername_2->setCurrentIndex(0);
    ui->showphonenumber_2->setCurrentIndex(0);
    ui->showemail_2->setCurrentIndex(0);
    ui->showfirstname_2->setCurrentIndex(0);
    ui->showlastname_2->setCurrentIndex(0);
    ui->showbio_2->setCurrentIndex(0);
}


void Setting::on_editcontacts_clicked()
{
    ui->winstack->setCurrentIndex(3);
}


void Setting::on_backbtn_3_clicked()
{
    ui->winstack->setCurrentIndex(0);
}


void Setting::on_uplButton_clicked()
{
    this->picName_2 = QFileDialog::getOpenFileName(this, tr("Open Image"), "/", tr("Image Files (*.png)"));
    if(this->picName_2 != "")
    {
        ui->profilepictureeditprofile->setText("<img src=\"file:///"+this->picName_2+"\" alt=\"Image read error!\" height=\"110\" width=\"110\" />");
    }
}


void Setting::on_saveeditprivacy_clicked()
{
    switch (ui->showpicture_2->currentIndex()) {
    case 1:
        howAmI.setPhotoAccessibility(1);
        break;
    case 2:
        howAmI.setPhotoAccessibility(2);
        break;
    default:
        break;
    }

    switch (ui->showusername_2->currentIndex()) {
    case 1:
        howAmI.setNameAccessibility(1);
        break;
    case 2:
        howAmI.setNameAccessibility(2);
        break;
    default:
        howAmI.setNameAccessibility(0);
        break;
    }

    switch (ui->showemail_2->currentIndex()) {
    case 1:
        howAmI.setEmailAccessibility(1);
        break;
    case 2:
        howAmI.setEmailAccessibility(2);
        break;
    default:
        howAmI.setEmailAccessibility(0);
        break;
    }

    switch (ui->showphonenumber_2->currentIndex()) {
    case 1:
        howAmI.setPhoneAccessibility(1);
        break;
    case 2:
        howAmI.setPhoneAccessibility(2);
        break;
    default:
        howAmI.setPhoneAccessibility(0);
        break;
    }

    switch (ui->showfirstname_2->currentIndex()) {
    case 1:
        howAmI.setFirstNameAccessibility(1);
        break;
    case 2:
        howAmI.setFirstNameAccessibility(2);
        break;
    default:
        howAmI.setFirstNameAccessibility(0);
        break;
    }

    switch (ui->showlastname_2->currentIndex()) {
    case 1:
        howAmI.setLastNameAccessibility(1);
        break;
    case 2:
        howAmI.setLastNameAccessibility(2);
        break;
    default:
        howAmI.setLastNameAccessibility(0);
        break;
    }

    switch (ui->showbio_2->currentIndex()) {
    case 1:
        howAmI.setBioAccessibility(1);
        break;
    case 2:
        howAmI.setBioAccessibility(2);
        break;
    default:
        howAmI.setBioAccessibility(0);
        break;
    }

    maindatabase::Modify_UserAAccessibility(howAmI);
    on_backbtn_2_clicked();
}

