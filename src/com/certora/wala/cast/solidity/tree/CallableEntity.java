package com.certora.wala.cast.solidity.tree;

import com.ibm.wala.cast.ir.translator.AbstractCodeEntity;
import com.ibm.wala.cast.tree.CAstEntity;
import com.ibm.wala.cast.tree.CAstNode;
import com.ibm.wala.cast.tree.CAstSourcePositionMap.Position;
import com.ibm.wala.cast.tree.CAstType;
import com.ibm.wala.cast.tree.CAstType.Function;

public abstract class CallableEntity extends AbstractCodeEntity {

	protected String[] argumentNames;
	protected String name;
	protected Position location;
	protected Position nameLocation;
	protected Position[] argLocations;

	public CallableEntity(String name,
			CAstType.Function type, 
			String[] argumentNames, 
			Position location,
			Position nameLocation,
			Position[] argLocations) 
	{
		super(type);
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
		return new CAstNode[0];
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

}