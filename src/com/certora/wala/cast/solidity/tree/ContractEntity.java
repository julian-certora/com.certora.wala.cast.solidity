package com.certora.wala.cast.solidity.tree;

import java.util.Collection;
import java.util.Collections;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import com.ibm.wala.cast.tree.CAstAnnotation;
import com.ibm.wala.cast.tree.CAstControlFlowMap;
import com.ibm.wala.cast.tree.CAstEntity;
import com.ibm.wala.cast.tree.CAstNode;
import com.ibm.wala.cast.tree.CAstNodeTypeMap;
import com.ibm.wala.cast.tree.CAstQualifier;
import com.ibm.wala.cast.tree.CAstSourcePositionMap;
import com.ibm.wala.cast.tree.CAstSourcePositionMap.Position;
import com.ibm.wala.cast.tree.CAstType;
import com.ibm.wala.util.collections.EmptyIterator;

public class ContractEntity implements CAstEntity {
	private final String name;
	private final CAstType type;
	private final Position sourcePosition;
	private final Position namePosition;
	private final Set<CAstEntity> entities;
	
	public ContractEntity(String name, CAstType type, Position sourcePosition, Position namePosition, Set<CAstEntity> entities) {
		this.name = name;
		this.type = type;
		this.namePosition = namePosition;
		this.sourcePosition = sourcePosition;
		this.entities = entities;
	}
	
	@Override
	public CAstNode getAST() {
		assert false;
		return null;
	}

	@Override
	public Map<CAstNode, Collection<CAstEntity>> getAllScopedEntities() {
		return Collections.singletonMap(null, entities);
	}

	@Override
	public Collection<CAstAnnotation> getAnnotations() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public int getArgumentCount() {
		return 0;
	}

	@Override
	public CAstNode[] getArgumentDefaults() {
		return null;
	}

	@Override
	public String[] getArgumentNames() {
		return null;
	}

	@Override
	public CAstControlFlowMap getControlFlow() {
		assert false;
		return null;
	}

	@Override
	public int getKind() {
		return CAstEntity.TYPE_ENTITY;
	}

	@Override
	public String getName() {
		return name;
	}

	@Override
	public Position getNamePosition() {
		return namePosition;
	}

	@Override
	public CAstNodeTypeMap getNodeTypeMap() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Position getPosition() {
		return sourcePosition;
	}

	@Override
	public Position getPosition(int arg) {
		assert false;
		return null;
	}

	@Override
	public Collection<CAstQualifier> getQualifiers() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Iterator<CAstEntity> getScopedEntities(CAstNode construct) {
		if (construct == null) {
			return entities.iterator();
		} else {
			return EmptyIterator.instance();
		}
	}

	@Override
	public String getSignature() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public CAstSourcePositionMap getSourceMap() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public CAstType getType() {
		return type;
	}

}
