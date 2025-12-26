package com.certora.wala.cast.solidity.loader;

import java.util.Arrays;
import java.util.Collection;
import java.util.List;

import com.ibm.wala.cast.tree.CAstType;
import com.ibm.wala.cast.tree.CAstType.Function;

public class FunctionType implements Function {

	private final String name;
	private final CAstType returnType;
	private CAstType[] args;

	public FunctionType(String name, CAstType returnType, CAstType... args) {
		this.name = name;
		this.returnType = returnType;
		this.args = args;
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
	public int getArgumentCount() {
		return args.length;
	}

	@Override
	public List<CAstType> getArgumentTypes() {
		return Arrays.asList(args);
	}

	@Override
	public Collection<CAstType> getExceptionTypes() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public CAstType getReturnType() {
		return returnType;
	}

}
