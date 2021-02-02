#ifndef SIMPLECRYPT_H
#define SIMPLECRYPT_H


// System and QT Includes
#include <QString>
#include <QVector>
#include <QFlags>

// own Includes
#include "datamanager.h"
     


class WMSMANAGER_API CdmCrypt
{
public:
   /**
   CompressionMode describes if compression will be applied to the data to be
   encrypted.
   */
   enum CompressionMode {
      CompressionAuto,    /*!< Only apply compression if that results in a shorter plaintext. */
      CompressionAlways,  /*!< Always apply compression. Note that for short inputs, a compression may result in longer data */
      CompressionNever    /*!< Never apply compression. */
   };
   /**
   IntegrityProtectionMode describes measures taken to make it possible to detect problems with the data
   or wrong decryption keys.

   Measures involve adding a checksum or a cryptograhpic hash to the data to be encrypted. This
   increases the length of the resulting cypertext, but makes it possible to check if the plaintext
   appears to be valid after decryption.
   */
   enum IntegrityProtectionMode {
      ProtectionNone,    /*!< The integerity of the encrypted data is not protected. It is not really possible to detect a wrong key, for instance. */
      ProtectionChecksum,/*!< A simple checksum is used to verify that the data is in order. If not, an empty string is returned. */
      ProtectionHash     /*!< A cryptographic hash is used to verify the integrity of the data. This method produces a much stronger, but longer check */
   };
   /**
   Error describes the type of error that occured.
   */
   enum Error {
      ErrorNoError,         /*!< No error occurred. */
      ErrorNoKeySet,        /*!< No key was set. You can not encrypt or decrypt without a valid key. */
      ErrorUnknownVersion,  /*!< The version of this data is unknown, or the data is otherwise not valid. */
      ErrorIntegrityFailed, /*!< The integrity check of the data failed. Perhaps the wrong key was used. */
   };


    //enum to describe options that have been used for the encryption. Currently only one, but
    //that only leaves room for future extensions like adding a cryptographic hash...
    enum CryptoFlag{CryptoFlagNone = 0,
                    CryptoFlagCompression = 0x01,
                    CryptoFlagChecksum = 0x02,
                    CryptoFlagHash = 0x04
    };
   
    private:
       quint64 m_key;
       QVector<char> m_keyParts;
       CompressionMode m_compressionMode;
       IntegrityProtectionMode m_protectionMode;
       Error m_lastError;

   public:
     
     bool hasKey() const {return !m_keyParts.isEmpty();}
  
     /**
       Sets the compression mode to use when encrypting data. The default mode is Auto.
  
       Note that decryption is not influenced by this mode, as the decryption recognizes
       what mode was used when encrypting.
       */
     void setCompressionMode(CompressionMode mode) {m_compressionMode = mode;}
     /**
       Returns the CompressionMode that is currently in use.
       */
     CompressionMode compressionMode() const {return m_compressionMode;}
  
     /**
       Sets the integrity mode to use when encrypting data. The default mode is Checksum.
  
       Note that decryption is not influenced by this mode, as the decryption recognizes
       what mode was used when encrypting.
       */
     void setIntegrityProtectionMode(IntegrityProtectionMode mode) {m_protectionMode = mode;}
     /**
       Returns the IntegrityProtectionMode that is currently in use.
       */
     IntegrityProtectionMode integrityProtectionMode() const {return m_protectionMode;}
  
     /**
       Returns the last error that occurred.
       */
     Error lastError() const {return m_lastError;}
  

   public:
   /** +-=---------------------------------------------------------Fr 22. Jun 09:59:03 2012-------*
    * @method  CdmCrypt::CdmCrypt                            // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 22. Jun 09:59:03 2012----------*/
    CdmCrypt( );

   public:
   /** +-=---------------------------------------------------------Fr 22. Jun 09:59:36 2012-------*
    * @method  CdmCrypt::CdmCrypt                            // public                            *
    * @return                                                //                                   *
    * @param   quint64 key                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 22. Jun 09:59:36 2012----------*/
    CdmCrypt( quint64 key);

   public:
   /** +-=---------------------------------------------------------Fr 22. Jun 10:25:56 2012-------*
    * @method  CdmCrypt::setKey                              // public                            *
    * @return  void                                          //                                   *
    * @param   quint64 key                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 22. Jun 10:25:56 2012----------*/
    void setKey(quint64 key);

   private:
   /** +-=---------------------------------------------------------Fr 22. Jun 10:01:05 2012-------*
    * @method  CdmCrypt::splitKey                            // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 22. Jun 10:01:05 2012----------*/
    void splitKey();

   public:
   /** +-=---------------------------------------------------------Fr 22. Jun 10:26:05 2012-------*
    * @method  CdmCrypt::encryptToByteArray                  // public                            *
    * @return  QByteArray                                    //                                   *
    * @param   const QString& plaintext                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 22. Jun 10:26:05 2012----------*/
    QByteArray encryptToByteArray(const QString& plaintext);

   public:
   /** +-=---------------------------------------------------------Fr 22. Jun 10:26:11 2012-------*
    * @method  CdmCrypt::encryptToByteArray                  // public                            *
    * @return  QByteArray                                    //                                   *
    * @param   QByteArray plaintext                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 22. Jun 10:26:11 2012----------*/
    QByteArray encryptToByteArray(QByteArray plaintext);

   public:
   /** +-=---------------------------------------------------------Fr 22. Jun 10:26:20 2012-------*
    * @method  CdmCrypt::encryptToString                     // public                            *
    * @return  QString                                       //                                   *
    * @param   const QString& plaintext                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 22. Jun 10:26:20 2012----------*/
    QString encryptToString(const QString& plaintext);

   public:
   /** +-=---------------------------------------------------------Fr 22. Jun 10:26:27 2012-------*
    * @method  CdmCrypt::encryptToString                     // public                            *
    * @return  QString                                       //                                   *
    * @param   QByteArray plaintext                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 22. Jun 10:26:27 2012----------*/
    QString encryptToString(QByteArray plaintext);

   public:
   /** +-=---------------------------------------------------------Fr 22. Jun 10:26:32 2012-------*
    * @method  CdmCrypt::decryptToString                     // public                            *
    * @return  QString                                       //                                   *
    * @param   const QString& cyphertext                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 22. Jun 10:26:32 2012----------*/
    QString decryptToString(const QString& cyphertext);

   public:
   /** +-=---------------------------------------------------------Fr 22. Jun 10:26:46 2012-------*
    * @method  CdmCrypt::decryptToString                     // public                            *
    * @return  QString                                       //                                   *
    * @param   QByteArray cypher                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 22. Jun 10:26:46 2012----------*/
    QString decryptToString(QByteArray cypher);

   public:
   /** +-=---------------------------------------------------------Fr 22. Jun 10:40:23 2012-------*
    * @method  CdmCrypt::decryptToByteArray                  // public                            *
    * @return  QByteArray                                    //                                   *
    * @param   const QString& cyphertext                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 22. Jun 10:40:23 2012----------*/
    QByteArray decryptToByteArray(const QString& cyphertext);

   public:
   /** +-=---------------------------------------------------------Fr 22. Jun 10:25:49 2012-------*
    * @method  CdmCrypt::~CdmCrypt                           // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmCrypt                                                   *
    *----------------last changed: -----------------------------Fr 22. Jun 10:25:49 2012----------*/
    virtual ~CdmCrypt( );

   public:
   /** +-=---------------------------------------------------------Fr 22. Jun 10:40:14 2012-------*
    * @method  CdmCrypt::decryptToByteArray                  // public                            *
    * @return  QByteArray                                    //                                   *
    * @param   QByteArray cyphertext                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 22. Jun 10:40:14 2012----------*/
    QByteArray decryptToByteArray(QByteArray cyphertext);
};
  
#endif // // SimpleCrypt_H
