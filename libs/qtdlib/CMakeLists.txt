set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(QTDLIB "QTdlib")

set(
    SRC
    auth/qtdauthstate.cpp
    auth/qtdauthcode.cpp
    auth/qtdauthstatefactory.cpp
    auth/qtdauthparametersresponse.cpp
    auth/qtdauthencryptionkeyresponse.cpp
    auth/qtdauthphonenumberresponse.cpp
    auth/qtdauthcoderesponse.cpp
    chat/qtdchat.cpp
    chat/qtdchatmemberstatus.cpp
    chat/qtdbasicgroupchat.cpp
    chat/qtdbasicgroupinfo.cpp
    chat/qtdsecretchat.cpp
    chat/qtdsecretchatstate.cpp
    chat/qtdsupergroupchat.cpp
    chat/qtdchattype.cpp
    chat/qtdchattypefactory.cpp
    chat/qtdchatlistmodel.cpp
    chat/qtdchatlistsortfiltermodel.cpp
    chat/requests/qtdgetbasicgrouprequest.cpp
    chat/requests/qtdgetchatsrequest.cpp
    chat/requests/qtdreportchatrequest.cpp
    chat/requests/qtdgetsecretchatrequest.cpp
    chat/requests/qtdgetsupergrouprequest.cpp
    common/qabstracttdobject.cpp
    common/qabstractint53id.cpp
    common/qabstractint32id.cpp
    common/qabstractint64id.cpp
    common/qtdint.cpp
    common/qtdrequest.cpp
    client/qtdhandle.cpp
    client/qtdclient.cpp
    client/qtdthread.cpp
    connections/qtdconnectionstate.cpp
    connections/qtdconnectionstatefactory.cpp
    files/qtdfile.cpp
    files/qtdlocalfile.cpp
    files/qtdremotefile.cpp
    files/qtddownloadfilerequest.cpp
    files/qtdphoto.cpp
    messages/qtdmessage.cpp
    models/QmlObjectListModel.cpp
    models/QmlVariantListModel.cpp
    notifications/qtdnotificationsettings.cpp
    user/qtduser.cpp
    user/qtdlinkstate.cpp
    user/qtdlinkstatefactory.cpp
    user/qtduserstatus.cpp
    user/qtdusertype.cpp
    user/qtduserstatusfactory.cpp
    user/qtdprofilephoto.cpp
    user/requests/qtdblockuserrequest.cpp
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_library(${QTDLIB} SHARED ${SRC})
target_link_libraries(${QTDLIB} Qt5::Core Qt5::Quick Qt5::Qml Qt5::Concurrent Td::TdJsonStatic)
target_include_directories(${QTDLIB} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
get_filename_component(QTDLIB_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set_property(TARGET ${QTDLIB} PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${QTDLIB_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

execute_process(
    COMMAND dpkg-architecture -qDEB_HOST_MULTIARCH
    OUTPUT_VARIABLE ARCH_TRIPLET
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(QT_IMPORTS_DIR "/lib/${ARCH_TRIPLET}")

install(TARGETS ${PLUGIN} DESTINATION ${QT_IMPORTS_DIR})
