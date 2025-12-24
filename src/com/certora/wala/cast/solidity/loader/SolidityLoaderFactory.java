package com.certora.wala.cast.solidity.loader;

import com.certora.wala.cast.solidity.types.SolidityTypes;
import com.ibm.wala.cast.loader.SingleClassLoaderFactory;
import com.ibm.wala.classLoader.IClassLoader;
import com.ibm.wala.ipa.cha.IClassHierarchy;
import com.ibm.wala.types.ClassLoaderReference;

public class SolidityLoaderFactory extends SingleClassLoaderFactory {

	@Override
	public ClassLoaderReference getTheReference() {
		return SolidityTypes.solidity;
	}

	@Override
	protected IClassLoader makeTheLoader(IClassHierarchy cha) {
		return new SolidityLoader(cha, null);
	}

}
