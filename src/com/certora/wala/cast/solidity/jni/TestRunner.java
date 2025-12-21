package com.certora.wala.cast.solidity.jni;

public class TestRunner {
	public static void main(String... args) {
		try (SolidityJNIBridge test = new SolidityJNIBridge()) {
			test.loadFiles(args);
			for(String f : test.files()) {
				System.out.println("file " + f);
				test.translate(f);
			}
		} catch (Exception e) {
			assert false : e;
		}
	}
}
