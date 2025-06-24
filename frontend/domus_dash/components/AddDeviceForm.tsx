"use client";

import { useState } from "react";

interface Props {
  onDeviceAdded: () => void;
  onCancel: () => void;
}

export default function AddDeviceForm({ onDeviceAdded, onCancel }: Props) {
  const [serial, setSerial] = useState("");
  const [error, setError] = useState("");

  const handleSubmit = async () => {
    const token = localStorage.getItem("token");
    const res = await fetch(`${process.env.NEXT_PUBLIC_API_URL}/api/devices`, {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${token}`,
      },
      body: JSON.stringify({ serial }),
    });

    if (res.ok) {
      setSerial("");
      setError("");
      onDeviceAdded();
      onCancel();
    } else {
      const msg = await res.text();
      setError(msg);
    }
  };

  return (
    <div className="w-full max-w-md bg-white rounded-lg shadow-md p-6 mt-6 border">
      <h3 className="text-lg font-semibold mb-2">Register New Device</h3>

      <input
        type="text"
        placeholder="Device Serial"
        value={serial}
        onChange={(e) => setSerial(e.target.value)}
        className="w-full border px-3 py-2 rounded mb-2"
      />

      {error && <p className="text-red-500 text-sm mb-2">{error}</p>}

      <div className="flex justify-end gap-2">
        <button className="px-4 py-2 bg-gray-300 rounded" onClick={onCancel}>
          Cancel
        </button>
        <button className="px-4 py-2 bg-blue-600 text-white rounded" onClick={handleSubmit}>
          Register
        </button>
      </div>
    </div>
  );
}