package com.certora.wala.cast.solidity.tree;

import java.util.Collection;

import com.ibm.wala.cast.ir.translator.AbstractCodeEntity;
import com.ibm.wala.cast.tree.CAstEntity;
import com.ibm.wala.cast.tree.CAstNode;
import com.ibm.wala.cast.tree.CAstQualifier;
import com.ibm.wala.cast.tree.CAstSourcePositionMap.Position;
import com.ibm.wala.cast.tree.CAstType;
import com.ibm.wala.cast.tree.CAstType.Function;

public class FunctionEntity extends AbstractCodeEntity {

	private String[] argumentNames;
	private String name;
	private Position location;
	private Position nameLocation;
	private Position[] argLocations;

	public FunctionEntity(String name,
			CAstType.Function type, 
			String[] argumentNames, 
			Position location,
			Position nameLocation,
			Position[] argLocations,
			CAstNode ast) {
		super(type);
		this.Ast = ast;
		this.name = name;
		this.location = location;
		this.nameLocation = nameLocation;
		this.argLocations = argLocations;
		this.argumentNames = argumentNames;
	}

	@Override
	public int getArgumentCount() {
		return ((Function)type).getArgumentCount();
	}

	@Override
	public CAstNode[] getArgumentDefaults() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public String[] getArgumentNames() {
		return argumentNames;
	}

	@Override
	public int getKind() {
		return CAstEntity.FUNCTION_ENTITY;
	}

	@Override
	public String getName() {
		return name;
	}

	@Override
	public Position getNamePosition() {
		return nameLocation;
	}

	@Override
	public Position getPosition() {
		return location;
	}

	@Override
	public Position getPosition(int arg) {
		return argLocations[arg];
	}

	@Override
	public Collection<CAstQualifier> getQualifiers() {
		// TODO Auto-generated method stub
		return null;
	}

}
