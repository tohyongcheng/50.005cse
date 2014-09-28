package cse.security;
import java.io.*;
import java.net.*;				//creating socket
import java.nio.ByteBuffer;			//Byte Buffer
import java.security.*;
import java.security.spec.X509EncodedKeySpec;

import sun.misc.BASE64Decoder;			//Base64 decoding
import sun.misc.BASE64Encoder;

import javax.crypto.*;
import javax.xml.bind.DatatypeConverter;		//convert data type of public key

public class TestClient {

	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub
		//set variables for port, socket
		final int port = 3344;
		Socket sock = null;
		//set variables for RSAKeySize, public key, private key
		final int RSAKeySize = 1024;
		PublicKey pubKey = null;
		PrivateKey priKey = null;
		Key serverPubKey = null;
		String clientText = "Hello Server! Here the authentication from client";
		byte[] plainText = clientText.getBytes("UTF8");
				
		
		//----------- setup connection by creating socket-----------
		try{
			System.out.println("Client is now establishing connection.");
			sock = new Socket(InetAddress.getLocalHost(),port);
			}catch(Exception e){
				e.printStackTrace();
			}
				
		//----------- generating RSA key pair for client--------------

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
				
		//-----------send client public key to server--------------
		try{
				
			System.out.println("Send client public key to server");
			System.out.println(DatatypeConverter.printHexBinary(pubKey.getEncoded()));
			ByteBuffer bbSend = ByteBuffer.allocate(4);
			bbSend.putInt(pubKey.getEncoded().length);
			sock.getOutputStream().write(bbSend.array());
			sock.getOutputStream().write(pubKey.getEncoded());
			sock.getOutputStream().flush();
			


		//-------receive public key of server------
			
			byte[] lenb = new byte[4];
			sock.getInputStream().read(lenb, 0, 4);
			ByteBuffer bbReceive = ByteBuffer.wrap(lenb);
			int len = bbReceive.getInt();
			System.out.println("Length of the public key is: " + len);
			
			byte[] sPubKeyBytes = new byte[len]; 
			sock.getInputStream().read(sPubKeyBytes); 
			System.out.println("Server Public Key:\n"+ 
			DatatypeConverter.printHexBinary(sPubKeyBytes));
			
			X509EncodedKeySpec ks = new X509EncodedKeySpec(sPubKeyBytes); 
			KeyFactory kf = KeyFactory.getInstance("RSA"); 
			serverPubKey = kf.generatePublic(ks); 
			System.out.println("Encoded Public Key:\n" + 
			DatatypeConverter.printHexBinary(serverPubKey.getEncoded()));
		
		}catch (Exception e) {
			e.printStackTrace();
		}
			
			
		//-----------receive message from server-------------------

		try{
			ObjectInputStream obIn = new ObjectInputStream(sock.getInputStream());
			Object obj = obIn.readObject();
			System.out.println("Received from server:\n" + obj);


		//----Base64-decoding and Decryption for received message----

			byte[] decoded = new BASE64Decoder().decodeBuffer((String) obj);
			System.out.println("Base64 Decoded:\n" + new String(decoded,"UTF8")); 
			System.out.println("Start decryption");
			Cipher cipher = Cipher.getInstance("RSA/ECB/PKCS1Padding");
			cipher.init(Cipher.DECRYPT_MODE, priKey);
			byte[] newPlainText = cipher.doFinal(decoded);
			System.out.println("Finish decryption:\n" + new String(newPlainText,"UTF8"));
			


		//------Send message to server now------
			
			System.out.println("Start Encryption for plainText"); 
			 
			cipher.init(Cipher.ENCRYPT_MODE, serverPubKey); 
			byte[] cipherText = cipher.doFinal(plainText); 
			 
			System.out.println("Finish Encryption to cipherText:\n"+ 
			new String(cipherText,"UTF8") ); 
			BASE64Encoder base64 = new BASE64Encoder();
			String encryptedValue = base64.encode(cipherText); 
			System.out.println("Base64 Encoded:\n" + encryptedValue);
		
			
			//Send encrypted message
			ObjectOutputStream obOut = new ObjectOutputStream(sock.getOutputStream()); 
			obOut.writeObject(encryptedValue); 
			obOut.flush(); 
			
		//-----------Close the connection---------------------------
			sock.close();

		}catch(Exception e){
				e.printStackTrace();
		}	

	}

}
