package com.certora.wala.cast.solidity.tree;

import java.util.Collection;

import com.ibm.wala.cast.tree.CAstNode;
import com.ibm.wala.cast.tree.CAstQualifier;
import com.ibm.wala.cast.tree.CAstSourcePositionMap.Position;
import com.ibm.wala.cast.tree.CAstType;

public class FunctionEntity extends CallableEntity {

	public FunctionEntity(String name,
			CAstType.Function type, 
			String[] argumentNames, 
			Position location,
			Position nameLocation,
			Position[] argLocations,
			CAstNode ast) {
		super(name, type, argumentNames, location, nameLocation, argLocations);
		this.Ast = ast;
	}

	@Override
	public Collection<CAstQualifier> getQualifiers() {
		// TODO Auto-generated method stub
		return null;
	}

}
