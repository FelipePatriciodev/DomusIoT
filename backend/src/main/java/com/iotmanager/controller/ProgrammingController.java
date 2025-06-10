package com.iotmanager.controller;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.iotmanager.model.Programming;
import com.iotmanager.service.ProgrammingService;

@RestController
@RequestMapping("/api/programming")
public class ProgrammingController {

    @Autowired
    private ProgrammingService programmingService;

    @PostMapping("/device/{deviceId}")
    public ResponseEntity<?> create(@PathVariable Long deviceId, @RequestBody Programming programming) {
        return ResponseEntity.ok(programmingService.createProgramming(programming, deviceId));
    }

    @GetMapping
    public List<Programming> list() {
        return programmingService.getAll();
    }
}
