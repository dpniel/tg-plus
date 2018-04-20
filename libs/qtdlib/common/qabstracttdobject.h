#ifndef QABSTRACTTDOBJECT_H
#define QABSTRACTTDOBJECT_H

#include <QObject>
#include <QJsonObject>

/**
 * @brief The QAbstractTdObject class
 *
 * Abstract base class all tdlib objects should inherit.
 *
 * All subclasses should call setType() during construction to indicate
 * the message type the class represents.
 */
class QAbstractTdObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Type type READ type NOTIFY typeChanged)
public:
    explicit QAbstractTdObject(QObject *parent = nullptr);

    /**
     * @brief Telegram Message Types
     */
    enum Type {
        UNKNOWN = -1, // Uninitialized state
        ANIMATION,
        AUDIO,
        AUTHENTICATION_CODE_INFO,
        AUTHENTICATION_CODE_TYPE_SMS,
        AUTHENTICATION_CODE_TYPE_TELEGRAM_MESSAGE,
        AUTHENTICATION_CODE_TYPE_CALL,
        AUTHENTICATION_CODE_TYPE_FLASH_CALL,
        AUTHORIZATION_STATE_CLOSED,
        AUTHORIZATION_STATE_CLOSING,
        AUTHORIZATION_STATE_LOGGING_OUT,
        AUTHORIZATION_STATE_READY,
        AUTHORIZATION_STATE_WAIT_CODE,
        AUTHORIZATION_STATE_WAIT_ENCRYPTION_KEY,
        AUTHORIZATION_STATE_WAIT_PASSWORD,
        AUTHORIZATION_STATE_WAIT_PHONE_NUMBER,
        AUTHORIZATION_STATE_WAIT_TDLIB_PARAMETERS,
        CHAT,
        CHAT_PHOTO,
        CHAT_TYPE_PRIVATE,
        CHAT_TYPE_BASIC_GROUP,
        CHAT_TYPE_SUPERGROUP,
        CHAT_TYPE_SECRET,
        CONNECTION_STATE_CONNECTING,
        CONNECTION_STATE_CONNECTING_TO_PROXY,
        CONNECTION_STATE_READY,
        CONNECTION_STATE_UPDATING,
        CONNECTION_STATE_WAITING_FOR_NETWORK,
        DOCUMENT,
        FILE,
        FORMATTED_TEXT,
        LINK_STATE_IS_CONTACT,
        LINK_STATE_KNOWS_PHONE_NUMBER,
        LINK_STATE_NONE,
        LOCAL_FILE,
        MESSAGE,
        MESSAGE_ANIMATION,
        MESSAGE_AUDIO,
        MESSAGE_DOCUMENT,
        MESSAGE_TEXT,
        MESSAGE_PHOTO,
        MESSAGE_STICKER,
        MESSAGE_VIDEO,
        MESSAGE_VIDEO_NOTE,
        MESSAGE_VOICE_NOTE,
        PHOTO,
        PHOTO_SIZE,
        PROFILE_PHOTO,
        REMOTE_FILE,
        STICKER,
        STICKER_SET_INFO,
        TEXT_ENTITY,
        TEXT_ENTITY_TYPE_MENTION,
        TEXT_ENTITY_TYPE_HASHTAG,
        TEXT_ENTITY_TYPE_BOT_COMMAND,
        TEXT_ENTITY_TYPE_URL,
        TEXT_ENTITY_TYPE_EMAIL_ADDRESS,
        TEXT_ENTITY_TYPE_BOLD,
        TEXT_ENTITY_TYPE_ITALIC,
        TEXT_ENTITY_TYPE_CODE,
        TEXT_ENTITY_TYPE_PRE,
        TEXT_ENTITY_TYPE_PRE_CODE,
        TEXT_ENTITY_TYPE_TEXT_URL,
        TEXT_ENTITY_TYPE_MENTION_NAME,
        USER,
        USER_STATUS_EMPTY,
        USER_STATUS_LAST_MONTH,
        USER_STATUS_LAST_WEEK,
        USER_STATUS_OFFLINE,
        USER_STATUS_ONLINE,
        USER_STATUS_RECENTLY,
        USER_TYPE_BOT,
        USER_TYPE_DELETED,
        USER_TYPE_REGULAR,
        USER_TYPE_UNKNOWN,
        VIDEO,
        VIDEO_NOTE,
        VOICE_NOTE,
        WEB_PAGE,
    };
    Q_ENUM(Type)

    Type type() const;

    virtual void unmarshalJson(const QJsonObject &json);
    virtual QJsonObject marshalJson();

signals:
    void typeChanged(Type type);

protected:
    void setType(const Type type);
    Type m_type;
};

#endif // QABSTRACTTDOBJECT_H
