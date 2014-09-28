package cse.security;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.security.Key;
import java.security.KeyFactory;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.SecureRandom;
import java.security.spec.X509EncodedKeySpec;

import javax.crypto.Cipher;
import javax.xml.bind.DatatypeConverter;

import sun.misc.BASE64Decoder;
import sun.misc.BASE64Encoder;
//Byte Buffer
//convert data type of public key
//Base64 encoding

public class TestServer {

	public static void main(String[] args) throws Exception {
		
		// TODO Auto-generated method stub
		//set variables for port number
		final int port = 3344;
		final int RSAKeySize = 1024;
		//set socket server, socket client, client public key
		ServerSocket server = null;
		Socket client = null;
		
		PublicKey pubKey = null;
		PrivateKey priKey = null;
		Key clientPubKey = null;
		//an authentication message from server
		//get the message into byte format
		String serverText = "Hello Client! Here the authentication from server";
		//get the message into byte format
		byte[] plainText = serverText.getBytes("UTF8");
				
		//----------- initialize socket connection----------------------
		try{

			server = new ServerSocket(port);
			System.out.println("Server is waiting for client on port "+server.getLocalPort());
			client = server.accept();
			System.out.println("TCP connection is established now");

			}catch(Exception e){
				e.printStackTrace();
			}

		
		
		//------ Creating own key-------
		try {
			System.out.println("Start generating RSA key");
			KeyPairGenerator RSAKeyGen = KeyPairGenerator.getInstance("RSA");
			SecureRandom random = new SecureRandom();
			RSAKeyGen.initialize(RSAKeySize, random);
			KeyPair pair = RSAKeyGen.generateKeyPair();
			pubKey = pair.getPublic();
			priKey = pair.getPrivate();
			System.out.println("Finish generating RSA key");
		}catch (Exception e){
			e.printStackTrace();
		}
		
		
		//-------- Send public key--------
		
		System.out.println("Send client public key to server");
		System.out.println(DatatypeConverter.printHexBinary(pubKey.getEncoded()));
		ByteBuffer bbSend = ByteBuffer.allocate(4);
		bbSend.putInt(pubKey.getEncoded().length);
		client.getOutputStream().write(bbSend.array());
		client.getOutputStream().write(pubKey.getEncoded());
		client.getOutputStream().flush();
		
		//--------Getting public key from client------
		try{
		
		byte[] lenb = new byte[4];
		client.getInputStream().read(lenb, 0, 4);
		ByteBuffer bbReceive = ByteBuffer.wrap(lenb);
		int len = bbReceive.getInt();
		System.out.println("Length of the public key is: " + len);
		
		
		byte[] cPubKeyBytes = new byte[len]; 
		client.getInputStream().read(cPubKeyBytes); 
		System.out.println("Client Public Key:\n"+ 
		DatatypeConverter.printHexBinary(cPubKeyBytes)); 
		                                                   
		
		X509EncodedKeySpec ks = new X509EncodedKeySpec(cPubKeyBytes); 
		KeyFactory kf = KeyFactory.getInstance("RSA"); 
		clientPubKey = kf.generatePublic(ks); 
		System.out.println("Encoded Public Key:\n" + 
		DatatypeConverter.printHexBinary(clientPubKey.getEncoded()));
		
		
		}catch (Exception e) {
			e.printStackTrace();
		}
				


		//----------- Encryption for the message--------------------------

		System.out.println("Start Encryption for plainText"); 
		 
		Cipher cipher = Cipher.getInstance("RSA/ECB/PKCS1Padding"); 
		cipher.init(Cipher.ENCRYPT_MODE, clientPubKey); 
		byte[] cipherText = cipher.doFinal(plainText); 
		 
		System.out.println("Finish Encryption to cipherText:\n"+ 
		 new String(cipherText,"UTF8") ); 

		
		

		//----------- Base64 encoding-------------------------------------

		BASE64Encoder base64 = new BASE64Encoder();
		String encryptedValue = base64.encode(cipherText); 
		System.out.println("Base64 Encoded:\n" + encryptedValue);
		
				
		//----------- send Message to client------------------------------
		
		ObjectOutputStream obOut = new ObjectOutputStream(client.getOutputStream()); 
		obOut.writeObject(encryptedValue); 
		obOut.flush(); 
		
		
		
		// Receive Message from client 
		ObjectInputStream obIn = new ObjectInputStream(client.getInputStream()); 
		Object obj = obIn.readObject(); 
		System.out.println("Received from server:\n" + obj);
		
		//Base64 Decoding
		byte[] deco = new BASE64Decoder().decodeBuffer((String) obj); 
		System.out.println("Base64 Decoded:\n" + new String(deco,"UTF8")); 
		 
		System.out.println("Start decryption"); 
		cipher.init(Cipher.DECRYPT_MODE, priKey); 
		byte[] newPlainText = cipher.doFinal(deco); 
		System.out.println("Finish decryption:\n" + new String(newPlainText,"UTF8")); 
		 
				

		//----------- close connection--------------------------------
		client.close();
	}


}
