"use client";

import { useEffect, useState } from "react";
import { useRouter } from "next/navigation";
import LogoutButton from "@/components/LogoutButton";
import AddDeviceForm from "@/components/AddDeviceForm";
import { HiTrash } from "react-icons/hi";
import { FiEdit } from "react-icons/fi";
import { MdPowerSettingsNew } from "react-icons/md";

interface Device {
  id: number;
  serial: string;
  status: boolean;
}

export default function Dashboard() {
  const router = useRouter();
  const [username, setUsername] = useState("");
  const [devices, setDevices] = useState<Device[]>([]);
  const [showAddForm, setShowAddForm] = useState(false);
  const [editingDeviceId, setEditingDeviceId] = useState<number | null>(null);
  const [editingSerial, setEditingSerial] = useState("");

  const token = typeof window !== "undefined" ? localStorage.getItem("token") : null;

  const fetchDevices = async () => {
    if (!token) return;
    const res = await fetch(`${process.env.NEXT_PUBLIC_API_URL}/api/devices`, {
      headers: { Authorization: `Bearer ${token}` },
    });
    if (res.ok) {
      const list = await res.json();
      setDevices(list);
    }
  };

  const fetchData = async () => {
    try {
      const validateRes = await fetch(`${process.env.NEXT_PUBLIC_API_URL}/api/auth/validate`, {
        headers: { Authorization: `Bearer ${token}` },
      });

      if (!validateRes.ok) {
        router.push("/login");
        return;
      }

      const meRes = await fetch(`${process.env.NEXT_PUBLIC_API_URL}/api/auth/me`, {
        headers: { Authorization: `Bearer ${token}` },
      });

      if (meRes.ok) {
        const userData = await meRes.json();
        setUsername(userData.username);
      }

      await fetchDevices();
    } catch {
      router.push("/login");
    }
  };

  useEffect(() => {
    if (!token) {
      router.push("/login");
      return;
    }
    fetchData();
  }, [router]);

  const handleDelete = async (id: number) => {
    const confirmed = window.confirm("Are you sure you want to delete this device?");
    if (!confirmed) return;

    const res = await fetch(`${process.env.NEXT_PUBLIC_API_URL}/api/devices/${id}`, {
      method: "DELETE",
      headers: {
        Authorization: `Bearer ${token}`,
      },
    });

    if (res.ok) {
      setDevices((prev) => prev.filter((d) => d.id !== id));
    } else {
      alert("Failed to delete device.");
    }
  };

  const handleUpdate = async (id: number) => {
    const res = await fetch(`${process.env.NEXT_PUBLIC_API_URL}/api/devices/${id}`, {
      method: "PUT",
      headers: {
        "Content-Type": "application/json",
        Authorization: `Bearer ${token}`,
      },
      body: JSON.stringify({ serial: editingSerial }),
    });

    if (res.ok) {
      setEditingDeviceId(null);
      setEditingSerial("");
      fetchDevices();
    } else {
      alert("Failed to update device.");
    }
  };

  return (
    <div>
      <header
        className="text-white flex items-center justify-between p-2 px-20"
        style={{ backgroundColor: "#004AAD" }}
      >
        <div>
          <h1 className="text-2xl font-bold">DomusIoT</h1>
          <h2 className="text-lg">Dashboard</h2>
        </div>
        <div className="flex items-center space-x-2">
          <p>{username}</p>
          <div className="w-10 h-10 rounded-full bg-white text-[#004AAD] flex items-center justify-center">
            <svg className="w-5 h-5" fill="currentColor" viewBox="0 0 24 24">
              <path d="M12 12c2.7 0 5-2.3 5-5s-2.3-5-5-5-5 2.3-5 5 2.3 5 5 5zm0 2c-3.3 0-10 1.7-10 5v3h20v-3c0-3.3-6.7-5-10-5z" />
            </svg>
          </div>
          <LogoutButton />
        </div>
      </header>

      <div className="min-h-screen bg-gray-100 flex flex-col items-center justify-start p-10">
        {devices.length === 0 ? (
          <>
            <p className="text-gray-500 text-lg mb-4">
              You don't have any registered devices yet.
            </p>
          </>
        ) : (
          <div className="grid grid-cols-3 gap-6 mb-6">
            {devices.map((device) => (
              <div
                key={device.id}
                className="w-64 h-40 bg-blue-700 rounded-lg shadow-md text-white p-4 flex flex-col justify-between"
              >
                <div>
                  {editingDeviceId === device.id ? (
                    <input
                      type="text"
                      value={editingSerial}
                      onChange={(e) => setEditingSerial(e.target.value)}
                      className="w-full text-black px-2 py-1 rounded mb-1"
                    />
                  ) : (
                    <p className="text-sm font-semibold">Serial: {device.serial}</p>
                  )}
                  <p>
                    Status:{" "}
                    <span className={device.status ? "text-green-400" : "text-red-400"}>
                      {device.status ? "On" : "Off"}
                    </span>
                  </p>
                </div>
                <div className="flex justify-end space-x-2 mt-2">
                  <button
                    onClick={() => handleDelete(device.id)}
                    className="text-red-300 hover:text-white text-xl"
                    title="Delete"
                  >
                    <HiTrash />
                  </button>

                  {editingDeviceId === device.id ? (
                    <button
                      onClick={() => handleUpdate(device.id)}
                      className="text-green-300 hover:text-white text-xl"
                      title="Save"
                    >
                      ✅
                    </button>
                  ) : (
                    <button
                      onClick={() => {
                        setEditingDeviceId(device.id);
                        setEditingSerial(device.serial);
                      }}
                      className="text-white hover:text-blue-200 text-xl"
                      title="Edit"
                    >
                      <FiEdit />
                    </button>
                  )}

                  <button
                    disabled
                    title="Send Command (soon)"
                    className="text-white opacity-40 cursor-not-allowed text-xl"
                  >
                    <MdPowerSettingsNew />
                  </button>
                </div>
              </div>
            ))}
          </div>
        )}

        {!showAddForm ? (
          <button
            onClick={() => setShowAddForm(true)}
            className="px-6 py-3 bg-gray-300 hover:bg-gray-400 transition rounded-lg shadow-md text-gray-700"
          >
            + Add New Device
          </button>
        ) : (
          <AddDeviceForm
            onDeviceAdded={fetchDevices}
            onCancel={() => setShowAddForm(false)}
          />
        )}
      </div>
    </div>
  );
}