package PublicExample;
import java.security.KeyPair;
import java.security.KeyPairGenerator;

import javax.crypto.Cipher;

import sun.misc.BASE64Encoder;

public class PublicKey {

	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub
		//		if (args.length != 1){
		//			System.err.println("Usage: Java PublicExample text");
		//			System.exit(1);
		//		}
		
		String message = "1000039";
		byte[] plainText = message.getBytes("UTF8");
		
		//generate a RSA key
		
		System.out.println("\nStart generating RSA key" );
		KeyPairGenerator keyGen = KeyPairGenerator.getInstance("RSA");
		keyGen.initialize(1024);
		KeyPair key = keyGen.generateKeyPair();
		System.out.println("Finish generating RSA key");
		
		//get an RSA cipher object and print the provider
		Cipher cipher = Cipher.getInstance("RSA/ECB/PKCS1Padding");
		System.out.println("\n" + cipher.getProvider().getInfo() );
		//
		//encrypt the plainText using the public key
		
		System.out.println("\nStart encryption" );
		cipher.init(Cipher.ENCRYPT_MODE, key.getPublic());
		byte[] cipherText = cipher.doFinal(plainText);
		System.out.println("Finish encryption: ");
		System.out.println(new String(cipherText, "UTF8"));
		System.out.println("Done");

		Base64Encoder base64 = new BASE64Encoder();
		String encryptedValue = base64.encode(cipherText);
		System.out.println("Base64: Encoded: \n" + encryptedValue);
		
		
		//decrypt the ciphertext using the private key
		
		System.out.println("\nStart decryption" );
		cipher.init(Cipher.DECRYPT_MODE, key.getPrivate());
		byte[] newPlainText = cipher.doFinal(cipherText);
		System.out.println("Finish decryption: " );
		System.out.println(new String(newPlainText, "UTF8") );

	}

}
