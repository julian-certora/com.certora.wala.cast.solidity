package com.certora.wala.cast.solidity.jni;

import com.ibm.wala.cast.util.CAstPrinter;

public class TestRunner {
	public static void main(String... args) throws Exception {
		try (SolidityJNIBridge test = new SolidityJNIBridge()) {
			test.loadFiles(args);
			System.out.println(test.files());
			for(String f : test.files()) {
				System.out.println("file " + f);
				System.out.println(CAstPrinter.print(test.translateFile(f)));
			}
		} catch (Exception e) {
			throw e;
			
		}
	}
}
