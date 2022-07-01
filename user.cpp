#include "user.h"
user::user()
{
    Accessibility = General ;
}
void user::set_ID(int in_ID)
{
    ID = in_ID ;
}
void user::set_UserName(QString in_UserName)
{
    UserName = in_UserName ;
}

void user::set_Password(QString in_Pass)
{
    Password = in_Pass ;
}

void user::set_Firstname(QString in_firstname)
{
    Firstname = in_firstname;
}
void user::set_Lastname(QString in_lastname)
{
    Lastname = in_lastname;
}
void user::set_BirthDate(QString in_BirthDate)
{
    BirthDate = in_BirthDate ;
}
void user::set_PhoneNumber(QString in_PhoneNumber)
{
    PhoneNumber =in_PhoneNumber ;
}
void user::set_EmailAddress(QString in_EmailAddress)
{
    EmailAddress = in_EmailAddress ;
}
int user::get_ID()
{
    return ID ;
}
QString user::get_UserName()
{
    return UserName ;
}
QString user::get_Password()
{
    return Password ;
}

QString user::get_firstname()
{
    return Firstname;
}
QString user::get_lastname()
{
    return Lastname;
}
QString user::get_PhoneNumber()
{
    return PhoneNumber ;
}
QString user::get_EmailAddress()
{
    return EmailAddress ;
}
QString user::get_BirthDate()
{
    return BirthDate ;
}
void user::set_PVchatID( QVector<int> in_PVchatsID)
{
    PVchatsID = in_PVchatsID ;
}
void user::set_GroupsID( QVector<int> in_GroupsID)
{
    GroupsID = in_GroupsID ;
}
void user::set_ChannelsID( QVector<int> in_ChannelsID)
{
    ChannelsID = in_ChannelsID ;
}
void user::set_FriendsID( QVector<int> in_FriendsID)
{
    FriendsID = in_FriendsID ;
}
QVector<int>  user::get_PVchatsID()
{
    return PVchatsID ;
}
QVector<int>  user::get_GroupsID()
{
     return GroupsID ;
}
QVector<int> user::get_ChannelsID()
{
    return ChannelsID ;
}
QVector<int> user::get_FriendsID()
{
    return FriendsID ;
}
void user::add_PVchatID(int in_chID)
{
    ChannelsID.push_back( in_chID ) ;
}
void user::add_GroupID(int in_gID)
{
    GroupsID.push_back( in_gID ) ;
}
void user::add_ChannelID(int in_chID)
{
    ChannelsID.push_back( in_chID ) ;
}
void user::add_FriendID(int in_FID)
{
    FriendsID.push_back( in_FID ) ;
}
void user::set_Accessibility( int in_Accessibility )
{
    if( in_Accessibility == 1)
        Accessibility = Friends ;
    if( in_Accessibility == 2)
        Accessibility = Nobody ;
    else
        Accessibility = General ;
}
Access user::get_Accessibility()
{
    return Accessibility ;
}
