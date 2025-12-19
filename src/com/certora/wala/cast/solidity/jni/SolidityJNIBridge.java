package com.certora.wala.cast.solidity.jni;

import java.util.List;

import com.ibm.wala.cast.ir.translator.NativeBridge;
import com.ibm.wala.cast.tree.impl.CAstImpl;

public class SolidityJNIBridge extends NativeBridge implements AutoCloseable {
	private static int ids = 0;
	
	private final int id = ids++;
	
	static {
		System.loadLibrary("walacastsolidity");
	}
	
	public SolidityJNIBridge() {
		super(new CAstImpl());
		init();
	}
	
	private native void init();
	
	public native void loadFiles(String[] filesAndNames);

	public native List<String> files();
	
	public native void translate(String fileName);
	
	@Override
	public native void close() throws Exception;
}
