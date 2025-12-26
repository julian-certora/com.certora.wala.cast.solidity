package com.certora.wala.cast.solidity.tree;

import java.util.Collection;
import java.util.Map;

import com.ibm.wala.cast.tree.CAstType;
import com.ibm.wala.util.collections.HashMapFactory;

public class SolidityCAstType implements CAstType.Primitive {

	private final String name;

	private SolidityCAstType(String name) {
		this.name = name;
	}
	
	@Override
	public String getName() {
		return name;
	}

	@Override
	public Collection<CAstType> getSupertypes() {
		return null;
	}

	@Override
	public String toString() {
		return "<" + name + ">";
	}
	
	public static final Map<String,CAstType> types = HashMapFactory.make();
	
	static {
		for(String nm : new String[] {"uint8", "uint256", "address", "string", "bool"}) {
			types.put(nm, new SolidityCAstType(nm));
		}
	}
	
	public static void record(String name, CAstType type) {
		assert !types.containsKey(name);
		types.put(name, type);
	}
	
	public static CAstType get(String name) {
		return types.get(name);
	}
}
